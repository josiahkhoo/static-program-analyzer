#include "simple_parser.h"

#include <stdexcept>
#include <vector>

SimpleParser::SimpleParser() = default;

Token SimpleParser::Peek(int pos) {
  if (pos >= tokens_.size()) {
    throw std::runtime_error("No more tokens left to Peek");
  }
  return tokens_[pos];
}

bool SimpleParser::MatchKind(Token::Kind kind) {
  return Peek(token_pos_).Is(kind);
}

bool SimpleParser::MatchString(const std::string &s) {
  return (Peek(token_pos_).GetValue() == s);
}

void SimpleParser::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token kind");
  }
}

void SimpleParser::Expect(const std::string &s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token string");
  }
}

TNode SimpleParser::Parse(std::vector<Token> tokens_) {
  try {
    this->tokens_ = tokens_;
    std::vector<std::shared_ptr<TNode>> children;

    do {
      children.emplace_back(ParseProcedure());
    } while (!MatchKind(Token::END));

    CheckValidProgram();

    t_node_id_++;
    TNode program_node = TNode(t_node_id_, TNode::Program, children);
    AssignParentToChildren(std::make_shared<TNode>(program_node), children);
    return program_node;
  } catch (const std::runtime_error &e) {
    TNode invalid_node(0, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());
    return invalid_node;
  }
}

std::shared_ptr<TNode> SimpleParser::ParseProcedure() {
  Expect("procedure");
  std::string proc_name_ = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);

  if (proc_map_.find(proc_name_) == proc_map_.end()) {
    curr_proc_ = proc_name_;
    std::unordered_set<std::string> empty_set;
    proc_map_.emplace(proc_name_, empty_set);
  } else {
    throw std::runtime_error("There are procedures with the same name!");
  }

  Expect(Token::LEFT_CURLY_BRACKET);
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseStatementList());
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  std::shared_ptr<TNode> procedure_node = std::make_shared<TNode>(
      t_node_id_, TNode::Procedure, proc_name_, children);
  AssignParentToChildren(procedure_node, children);
  return procedure_node;
}

std::shared_ptr<TNode> SimpleParser::ParseStatementList() {
  std::vector<std::shared_ptr<TNode>> children;

  do {
    children.emplace_back(ParseStatement());
  } while (!MatchKind(Token::RIGHT_CURLY_BRACKET));

  t_node_id_++;
  std::shared_ptr<TNode> statement_list_node =
      std::make_shared<TNode>(t_node_id_, TNode::StatementList, children);
  AssignParentToChildren(statement_list_node, children);
  return statement_list_node;
}

std::shared_ptr<TNode> SimpleParser::ParseStatement() {
  statement_number_++;

  // Check if next token is '=', it is an assignment if it is.
  if (Peek(token_pos_ + 1).Is(Token::EQUAL)) {
    return ParseAssign();
  }

  if (!MatchKind(Token::IDENTIFIER)) {
    throw std::runtime_error("Expected IDENTIFIER but got something else");
  }

  if (Peek(token_pos_).GetValue() == "read") {
    return ParseRead();
  } else if (Peek(token_pos_).GetValue() == "print") {
    return ParsePrint();
  } else if (Peek(token_pos_).GetValue() == "call") {
    return ParseCall();
  } else if (Peek(token_pos_).GetValue() == "while") {
    return ParseWhile();
  } else if (Peek(token_pos_).GetValue() == "if") {
    return ParseIf();
  } else {
    throw std::runtime_error("Failed to parse statement with Token name " +
                             Peek(token_pos_).GetValue());
  }
}

std::shared_ptr<TNode> SimpleParser::ParseAssign() {
  std::vector<std::shared_ptr<TNode>> children;

  // Parse var name on lhs
  children.emplace_back(ParseVarName());
  Expect(Token::EQUAL);

  // Parse Expr on rhs
  children.emplace_back(ParseExpr());
  Expect(Token::SEMICOLON);

  t_node_id_++;
  auto assign_node = std::make_shared<TNode>(t_node_id_, TNode::Assign,
                                             statement_number_, children);
  AssignParentToChildren(assign_node, children);
  return assign_node;
}

std::shared_ptr<TNode> SimpleParser::ParseRead() {
  Expect("read");
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseVarName());
  Expect(Token::SEMICOLON);

  t_node_id_++;
  auto read_node = std::make_shared<TNode>(t_node_id_, TNode::Read,
                                           statement_number_, children);
  AssignParentToChildren(read_node, children);
  return read_node;
}

std::shared_ptr<TNode> SimpleParser::ParsePrint() {
  Expect("print");
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseVarName());
  Expect(Token::SEMICOLON);

  t_node_id_++;
  auto print_node = std::make_shared<TNode>(t_node_id_, TNode::Print,
                                            statement_number_, children);
  AssignParentToChildren(print_node, children);
  return print_node;
}

std::shared_ptr<TNode> SimpleParser::ParseCall() {
  Expect("call");
  std::string call_proc_name = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);
  Expect(Token::SEMICOLON);

  if (call_proc_name != curr_proc_) {
    proc_map_[curr_proc_].emplace(call_proc_name);
  } else {
    throw std::runtime_error("Recursive procedure calling!");
  }

  t_node_id_++;
  std::shared_ptr<TNode> call_node = std::make_shared<TNode>(
      t_node_id_, TNode::Call, statement_number_, call_proc_name);
  return call_node;
}

std::shared_ptr<TNode> SimpleParser::ParseWhile() {
  Expect("while");
  int while_statement_number_ = statement_number_;
  std::vector<std::shared_ptr<TNode>> children;

  Expect(Token::LEFT_ROUND_BRACKET);
  children.emplace_back((ParseCondExpr()));
  Expect(Token::RIGHT_ROUND_BRACKET);

  Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  std::shared_ptr<TNode> while_node = std::make_shared<TNode>(
      t_node_id_, TNode::While, while_statement_number_, children);
  AssignParentToChildren(while_node, children);
  return while_node;
}

std::shared_ptr<TNode> SimpleParser::ParseIf() {
  Expect("if");
  int if_statement_number_ = statement_number_;
  std::vector<std::shared_ptr<TNode>> children;

  // Parse condition
  Expect(Token::LEFT_ROUND_BRACKET);
  children.emplace_back((ParseCondExpr()));
  Expect(Token::RIGHT_ROUND_BRACKET);

  // Parse 'then' statement list
  Expect("then");
  Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  Expect(Token::RIGHT_CURLY_BRACKET);

  // Parse 'else' statement list
  Expect("else");
  Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  std::shared_ptr<TNode> if_node = std::make_shared<TNode>(
      t_node_id_, TNode::IfElseThen, if_statement_number_, children);
  AssignParentToChildren(if_node, children);
  return if_node;
}

std::shared_ptr<TNode> SimpleParser::ParseCondExpr() {
  // rel_expr | '!' '(' cond_expr ')' |
  // '(' cond_expr ')' '&&' '(' cond_expr ')' |
  // '(' cond_expr ')' '||' '(' cond_expr ')'

  // Check for empty condition
  if (MatchKind(Token::RIGHT_ROUND_BRACKET)) {
    throw std::runtime_error("Empty condition!");
  }

  //Check for rel_expr
  int saved_token_pos =  token_pos_;
  try {
    std::shared_ptr<TNode> success = ParseRelExpr();
    return success;
  } catch (const std::exception &){
    token_pos_ = saved_token_pos;
  }

  if (MatchKind(Token::NOT)) {
    // '!' '(' cond_expr ')'
    Expect(Token::NOT);
    std::vector<std::shared_ptr<TNode>> children;

    Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    std::shared_ptr<TNode> not_node = std::make_shared<TNode>(
        t_node_id_, TNode::Not, statement_number_, children);
    AssignParentToChildren(not_node, children);
    return not_node;
  } else if (MatchKind(Token::LEFT_ROUND_BRACKET)) {
    // '(' cond_expr ')' '&&' '(' cond_expr ')' |
    // '(' cond_expr ')' '||' '(' cond_expr ')'
    std::vector<std::shared_ptr<TNode>> children;

    Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    Expect(Token::RIGHT_ROUND_BRACKET);

    TNode::Type type;
    if (MatchKind(Token::AND)) {
      // '(' cond_expr ')' '&&' '(' cond_expr ')'
      Expect(Token::AND);
      type = TNode::And;
    } else if (MatchKind(Token::OR)) {
      //'(' cond_expr ')' '||' '(' cond_expr ')'
      Expect(Token::OR);
      type = TNode::Or;
    } else {
      throw std::runtime_error(
          "Expected boolean operator but got something else!");
    }

    Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    std::shared_ptr<TNode> cond_node =
        std::make_shared<TNode>(t_node_id_, type, statement_number_, children);
    AssignParentToChildren(cond_node, children);
    return cond_node;
  } else {
    throw std::runtime_error("Invalid CondExpr!");
  }
}

std::shared_ptr<TNode> SimpleParser::ParseRelExpr() {
  // rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
  // rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
  // rel_factor '==' rel_factor | rel_factor '!=' rel_factor
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back((ParseRelFactor()));

  TNode::Type type;
  if (MatchKind(Token::GREATER_THAN)) {
    Expect(Token::GREATER_THAN);
    type = TNode::Greater;
  } else if (MatchKind(Token::GREATER_THAN_OR_EQUAL)) {
    Expect(Token::GREATER_THAN_OR_EQUAL);
    type = TNode::GreaterThanEqual;
  } else if (MatchKind(Token::LESS_THAN)) {
    Expect(Token::LESS_THAN);
    type = TNode::Lesser;
  } else if (MatchKind(Token::LESS_THAN_OR_EQUAL)) {
    Expect(Token::LESS_THAN_OR_EQUAL);
    type = TNode::LesserThanEqual;
  } else if (MatchKind(Token::DOUBLE_EQUAL)) {
    Expect(Token::DOUBLE_EQUAL);
    type = TNode::Equal;
  } else if (MatchKind(Token::NOT_EQUAL)) {
    Expect(Token::NOT_EQUAL);
    type = TNode::NotEqual;
  } else {
    throw std::runtime_error(
        "Expected rel expr operator but got something else!");
  }

  children.emplace_back((ParseRelFactor()));

  t_node_id_++;
  std::shared_ptr<TNode> rel_expr_node =
      std::make_shared<TNode>(t_node_id_, type, statement_number_, children);
  AssignParentToChildren(rel_expr_node, children);
  return rel_expr_node;
}

std::shared_ptr<TNode> SimpleParser::ParseRelFactor() {
  // var_name | const_value | expr
  return ParseExpr();
}

std::shared_ptr<TNode> SimpleParser::ParseExpr() {
  // expr '+' term | expr '-' term | term
  std::shared_ptr<TNode> expr_node = ParseTerm();
  while (!MatchKind(Token::END) &&
         ((MatchKind(Token::PLUS)) || MatchKind(Token::MINUS))) {
    std::vector<std::shared_ptr<TNode>> children;

    TNode::Type type;
    if (MatchKind(Token::PLUS)) {
      // '+'
      Expect(Token::PLUS);
      type = TNode::Plus;
    } else {
      // '-'
      Expect(Token::MINUS);
      type = TNode::Minus;
    }

    children.emplace_back((expr_node));

    children.emplace_back((ParseTerm()));

    t_node_id_++;
    std::shared_ptr<TNode> new_expr_node =
        std::make_shared<TNode>(t_node_id_, type, statement_number_, children);
    AssignParentToChildren(new_expr_node, children);

    expr_node = new_expr_node;
  }
  return expr_node;
}

std::shared_ptr<TNode> SimpleParser::ParseTerm() {
  // term '*' factor | term '/' factor | term '%' factor | factor
  std::shared_ptr<TNode> term_node = ParseFactor();
  while (!MatchKind(Token::END) &&
         ((MatchKind(Token::ASTERISK)) || MatchKind(Token::SLASH) ||
          MatchKind(Token::PERCENT))) {
    std::vector<std::shared_ptr<TNode>> children;

    TNode::Type type;
    if (MatchKind(Token::ASTERISK)) {
      // '*'
      Expect(Token::ASTERISK);
      type = TNode::Multiply;
    } else if (MatchKind(Token::SLASH)) {
      // '/'
      Expect(Token::SLASH);
      type = TNode::Divide;
    } else {
      // '%'
      Expect(Token::PERCENT);
      type = TNode::Modulo;
    }

    // Emplace lhs node ptr
    children.emplace_back(term_node);

    // Emplace rhs factor
    children.emplace_back(ParseFactor());

    t_node_id_++;
    std::shared_ptr<TNode> new_term_node =
        std::make_shared<TNode>(t_node_id_, type, statement_number_, children);
    AssignParentToChildren(new_term_node, children);

    term_node = new_term_node;
  }
  return term_node;
}

std::shared_ptr<TNode> SimpleParser::ParseFactor() {
  // var_name | const_value | '(' expr ')'
  if (MatchKind(Token::IDENTIFIER)) {
    return ParseVarName();
  } else if (MatchKind(Token::NUMBER)) {
    return ParseConstValue();
  } else {
    Expect(Token::LEFT_ROUND_BRACKET);
    auto factor_node = ParseExpr();
    Expect(Token::RIGHT_ROUND_BRACKET);
    return factor_node;
  }
}

std::shared_ptr<TNode> SimpleParser::ParseVarName() {
  std::string var_name_ = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);

  t_node_id_++;
  std::shared_ptr<TNode> name_node = std::make_shared<TNode>(
      t_node_id_, TNode::Variable, statement_number_, var_name_);
  return name_node;
}

std::shared_ptr<TNode> SimpleParser::ParseConstValue() {
  int const_value_ = stoi(Peek(token_pos_).GetValue());
  Expect(Token::NUMBER);

  t_node_id_++;
  std::shared_ptr<TNode> const_value_node = std::make_shared<TNode>(
      t_node_id_, TNode::Constant, statement_number_, const_value_);
  return const_value_node;
}

void SimpleParser::AssignParentToChildren(
    std::shared_ptr<TNode> t_node,
    const std::vector<std::shared_ptr<TNode>> &children) {
  for (const auto &child : children) {
    child->SetParent(t_node);
  }
}

void SimpleParser::CheckValidProgram() {
  for (const auto &proc_pair : proc_map_) {
    auto proc_start = proc_pair.first;
    auto proc_end = proc_pair.first;
    auto children = proc_map_[proc_start];
    TraverseProcedureTree(children, proc_start, proc_end);
  }
}

void SimpleParser::TraverseProcedureTree(
    std::unordered_set<std::string> &children, std::string &start,
    std::string &end) {
  for (const auto &child : children) {
    end = child;
    if (end == start) {
      throw std::runtime_error("Cyclic procedure calling!");
    }
    if (proc_map_.find(end) == proc_map_.end()) {
      throw std::runtime_error("Called procedure not found!");
    }
    auto next_children = proc_map_[child];
    if (next_children.empty()) {
      break;
    }
    TraverseProcedureTree(next_children, start, end);
  }
}
