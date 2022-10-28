#include "simple_parser.h"

#include <stdexcept>
#include <vector>

SimpleParser::SimpleParser() = default;

TNode SimpleParser::Parse(std::vector<Token> tokens) {
  try {
    std::vector<std::shared_ptr<TNode>> children;
    tokens_ = std::make_shared<TokenHandler>(TokenHandler(tokens));

    do {
      children.emplace_back(ParseProcedure());
    } while (!tokens_->MatchKind(Token::END));

    CheckValidProgram();

    t_node_id_++;
    TNode program_node = TNode(t_node_id_, TNode::Program, children);
    AssignParentToChildren(std::make_shared<TNode>(program_node), children);
    return program_node;
  } catch (const SyntaxException &e) {
    TNode invalid_node(0, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());
    return invalid_node;
  }
}

std::shared_ptr<TNode> SimpleParser::ParseProcedure() {
  tokens_->Expect("procedure");
  std::string proc_name_ = tokens_->PeekValue();
  tokens_->Expect(Token::IDENTIFIER);

  if (proc_map_.find(proc_name_) == proc_map_.end()) {
    curr_proc_ = proc_name_;
    std::unordered_set<std::string> empty_set;
    proc_map_.emplace(proc_name_, empty_set);
  } else {
    throw SyntaxException("There are procedures with the same name!");
  }

  tokens_->Expect(Token::LEFT_CURLY_BRACKET);
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseStatementList());
  tokens_->Expect(Token::RIGHT_CURLY_BRACKET);

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
  } while (!tokens_->MatchKind(Token::RIGHT_CURLY_BRACKET));

  t_node_id_++;
  std::shared_ptr<TNode> statement_list_node =
      std::make_shared<TNode>(t_node_id_, TNode::StatementList, children);
  AssignParentToChildren(statement_list_node, children);
  return statement_list_node;
}

std::shared_ptr<TNode> SimpleParser::ParseStatement() {
  statement_number_++;

  // Check if next token is '=', it is an assignment if it is.
  tokens_->Forward();
  if (tokens_->Peek().Is(Token::EQUAL)) {
    tokens_->Back();
    return ParseAssign();
  }
  tokens_->Back();

  if (!tokens_->MatchKind(Token::IDENTIFIER)) {
    throw SyntaxException("Expected IDENTIFIER but got something else");
  }

  if (tokens_->PeekValue() == "read") {
    return ParseRead();
  } else if (tokens_->PeekValue() == "print") {
    return ParsePrint();
  } else if (tokens_->PeekValue() == "call") {
    return ParseCall();
  } else if (tokens_->PeekValue() == "while") {
    return ParseWhile();
  } else if (tokens_->PeekValue() == "if") {
    return ParseIf();
  } else {
    throw SyntaxException("Failed to Parse statement with Token name " +
                             tokens_->PeekValue());
  }
}

std::shared_ptr<TNode> SimpleParser::ParseAssign() {
  std::vector<std::shared_ptr<TNode>> children;

  // Parse var name on lhs
  children.emplace_back(ParseVarName());
  tokens_->Expect(Token::EQUAL);

  // Parse Expr on rhs
  children.emplace_back(ParseExpr());
  tokens_->Expect(Token::SEMICOLON);

  t_node_id_++;
  auto assign_node = std::make_shared<TNode>(t_node_id_, TNode::Assign,
                                             statement_number_, children);
  AssignParentToChildren(assign_node, children);
  return assign_node;
}

std::shared_ptr<TNode> SimpleParser::ParseRead() {
  tokens_->Expect("read");
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseVarName());
  tokens_->Expect(Token::SEMICOLON);

  t_node_id_++;
  auto read_node = std::make_shared<TNode>(t_node_id_, TNode::Read,
                                           statement_number_, children);
  AssignParentToChildren(read_node, children);
  return read_node;
}

std::shared_ptr<TNode> SimpleParser::ParsePrint() {
  tokens_->Expect("print");
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back(ParseVarName());
  tokens_->Expect(Token::SEMICOLON);

  t_node_id_++;
  auto print_node = std::make_shared<TNode>(t_node_id_, TNode::Print,
                                            statement_number_, children);
  AssignParentToChildren(print_node, children);
  return print_node;
}

std::shared_ptr<TNode> SimpleParser::ParseCall() {
  tokens_->Expect("call");
  std::string call_proc_name = tokens_->PeekValue();
  tokens_->Expect(Token::IDENTIFIER);
  tokens_->Expect(Token::SEMICOLON);

  if (call_proc_name != curr_proc_) {
    proc_map_[curr_proc_].emplace(call_proc_name);
  } else {
    throw SyntaxException("Recursive procedure calling!");
  }

  t_node_id_++;
  std::shared_ptr<TNode> call_node = std::make_shared<TNode>(
      t_node_id_, TNode::Call, statement_number_, call_proc_name);
  return call_node;
}

std::shared_ptr<TNode> SimpleParser::ParseWhile() {
  tokens_->Expect("while");
  int while_statement_number_ = statement_number_;
  std::vector<std::shared_ptr<TNode>> children;

  tokens_->Expect(Token::LEFT_ROUND_BRACKET);
  children.emplace_back((ParseCondExpr()));
  tokens_->Expect(Token::RIGHT_ROUND_BRACKET);

  tokens_->Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  tokens_->Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  std::shared_ptr<TNode> while_node = std::make_shared<TNode>(
      t_node_id_, TNode::While, while_statement_number_, children);
  AssignParentToChildren(while_node, children);
  return while_node;
}

std::shared_ptr<TNode> SimpleParser::ParseIf() {
  tokens_->Expect("if");
  int if_statement_number_ = statement_number_;
  std::vector<std::shared_ptr<TNode>> children;

  // Parse condition
  tokens_->Expect(Token::LEFT_ROUND_BRACKET);
  children.emplace_back((ParseCondExpr()));
  tokens_->Expect(Token::RIGHT_ROUND_BRACKET);

  // Parse 'then' statement list
  tokens_->Expect("then");
  tokens_->Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  tokens_->Expect(Token::RIGHT_CURLY_BRACKET);

  // Parse 'else' statement list
  tokens_->Expect("else");
  tokens_->Expect(Token::LEFT_CURLY_BRACKET);
  children.emplace_back((ParseStatementList()));
  tokens_->Expect(Token::RIGHT_CURLY_BRACKET);

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
  if (tokens_->MatchKind(Token::RIGHT_ROUND_BRACKET)) {
    throw SyntaxException("Empty condition!");
  }

  // Check for rel_expr
  int saved_token_pos = tokens_->GetTokenPos();
  try {
    std::shared_ptr<TNode> success = ParseRelExpr();
    return success;
  } catch (const std::exception &) {
    tokens_->SetTokenPos(saved_token_pos);
  }

  if (tokens_->MatchKind(Token::NOT)) {
    // '!' '(' cond_expr ')'
    tokens_->Expect(Token::NOT);
    std::vector<std::shared_ptr<TNode>> children;

    tokens_->Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    tokens_->Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    std::shared_ptr<TNode> not_node = std::make_shared<TNode>(
        t_node_id_, TNode::Not, statement_number_, children);
    AssignParentToChildren(not_node, children);
    return not_node;
  } else if (tokens_->MatchKind(Token::LEFT_ROUND_BRACKET)) {
    // '(' cond_expr ')' '&&' '(' cond_expr ')' |
    // '(' cond_expr ')' '||' '(' cond_expr ')'
    std::vector<std::shared_ptr<TNode>> children;

    tokens_->Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    tokens_->Expect(Token::RIGHT_ROUND_BRACKET);

    TNode::Type type;
    if (tokens_->MatchKind(Token::AND)) {
      // '(' cond_expr ')' '&&' '(' cond_expr ')'
      tokens_->Expect(Token::AND);
      type = TNode::And;
    } else if (tokens_->MatchKind(Token::OR)) {
      //'(' cond_expr ')' '||' '(' cond_expr ')'
      tokens_->Expect(Token::OR);
      type = TNode::Or;
    } else {
      throw SyntaxException(
          "Expected boolean operator but got something else!");
    }

    tokens_->Expect(Token::LEFT_ROUND_BRACKET);
    children.emplace_back((ParseCondExpr()));
    tokens_->Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    std::shared_ptr<TNode> cond_node =
        std::make_shared<TNode>(t_node_id_, type, statement_number_, children);
    AssignParentToChildren(cond_node, children);
    return cond_node;
  } else {
    throw SyntaxException("Invalid CondExpr!");
  }
}

std::shared_ptr<TNode> SimpleParser::ParseRelExpr() {
  // rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
  // rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
  // rel_factor '==' rel_factor | rel_factor '!=' rel_factor
  std::vector<std::shared_ptr<TNode>> children;
  children.emplace_back((ParseRelFactor()));

  TNode::Type type;
  if (tokens_->MatchKind(Token::GREATER_THAN)) {
    tokens_->Expect(Token::GREATER_THAN);
    type = TNode::Greater;
  } else if (tokens_->MatchKind(Token::GREATER_THAN_OR_EQUAL)) {
    tokens_->Expect(Token::GREATER_THAN_OR_EQUAL);
    type = TNode::GreaterThanEqual;
  } else if (tokens_->MatchKind(Token::LESS_THAN)) {
    tokens_->Expect(Token::LESS_THAN);
    type = TNode::Lesser;
  } else if (tokens_->MatchKind(Token::LESS_THAN_OR_EQUAL)) {
    tokens_->Expect(Token::LESS_THAN_OR_EQUAL);
    type = TNode::LesserThanEqual;
  } else if (tokens_->MatchKind(Token::DOUBLE_EQUAL)) {
    tokens_->Expect(Token::DOUBLE_EQUAL);
    type = TNode::Equal;
  } else if (tokens_->MatchKind(Token::NOT_EQUAL)) {
    tokens_->Expect(Token::NOT_EQUAL);
    type = TNode::NotEqual;
  } else {
    throw SyntaxException(
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
  while (
      !tokens_->MatchKind(Token::END) &&
      ((tokens_->MatchKind(Token::PLUS)) || tokens_->MatchKind(Token::MINUS))) {
    std::vector<std::shared_ptr<TNode>> children;

    TNode::Type type;
    if (tokens_->MatchKind(Token::PLUS)) {
      // '+'
      tokens_->Expect(Token::PLUS);
      type = TNode::Plus;
    } else {
      // '-'
      tokens_->Expect(Token::MINUS);
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
  while (!tokens_->MatchKind(Token::END) &&
         ((tokens_->MatchKind(Token::ASTERISK)) ||
          tokens_->MatchKind(Token::SLASH) ||
          tokens_->MatchKind(Token::PERCENT))) {
    std::vector<std::shared_ptr<TNode>> children;

    TNode::Type type;
    if (tokens_->MatchKind(Token::ASTERISK)) {
      // '*'
      tokens_->Expect(Token::ASTERISK);
      type = TNode::Multiply;
    } else if (tokens_->MatchKind(Token::SLASH)) {
      // '/'
      tokens_->Expect(Token::SLASH);
      type = TNode::Divide;
    } else {
      // '%'
      tokens_->Expect(Token::PERCENT);
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
  if (tokens_->MatchKind(Token::IDENTIFIER)) {
    return ParseVarName();
  } else if (tokens_->MatchKind(Token::NUMBER)) {
    return ParseConstValue();
  } else {
    tokens_->Expect(Token::LEFT_ROUND_BRACKET);
    auto factor_node = ParseExpr();
    tokens_->Expect(Token::RIGHT_ROUND_BRACKET);
    return factor_node;
  }
}

std::shared_ptr<TNode> SimpleParser::ParseVarName() {
  std::string var_name_ = tokens_->PeekValue();
  tokens_->Expect(Token::IDENTIFIER);

  t_node_id_++;
  std::shared_ptr<TNode> name_node = std::make_shared<TNode>(
      t_node_id_, TNode::Variable, statement_number_, var_name_);
  return name_node;
}

std::shared_ptr<TNode> SimpleParser::ParseConstValue() {
  int const_value_ = stoi(tokens_->PeekValue());
  tokens_->Expect(Token::NUMBER);

  t_node_id_++;
  std::shared_ptr<TNode> const_value_node = std::make_shared<TNode>(
      t_node_id_, TNode::Constant, statement_number_, const_value_);
  return const_value_node;
}

void SimpleParser::AssignParentToChildren(
    const std::shared_ptr<TNode> &t_node,
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
      throw SyntaxException("Cyclic procedure calling!");
    }
    if (proc_map_.find(end) == proc_map_.end()) {
      throw SyntaxException("Called procedure not found!");
    }
    auto next_children = proc_map_[child];
    if (next_children.empty()) {
      break;
    }
    TraverseProcedureTree(next_children, start, end);
  }
}
