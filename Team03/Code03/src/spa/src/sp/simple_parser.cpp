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

bool SimpleParser::MatchString(const std::string& s) {
  return (Peek(token_pos_).GetValue() == s);
}

void SimpleParser::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token kind");
  }
}

void SimpleParser::Expect(const std::string& s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token string");
  }
}

TNode SimpleParser::Parse(std::vector<Token> tokens_) {
  try {
    this->tokens_ = tokens_;
    std::vector<std::shared_ptr<TNode>> children_;

    do {
      std::shared_ptr<TNode> shared_children_node_ptr_ =
          std::make_shared<TNode>(ParseProcedure());
      children_.emplace_back(shared_children_node_ptr_);
    } while (!MatchKind(Token::END));

    t_node_id_++;
    TNode program_node_(t_node_id_, TNode::Program, children_);
    return program_node_;
  } catch (const std::runtime_error& e_) {
    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());
    return invalid_node_;
  }
}

TNode SimpleParser::ParseProcedure() {
  Expect("procedure");
  std::string proc_name_ = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);

  Expect(Token::LEFT_CURLY_BRACKET);
  std::vector<std::shared_ptr<TNode>> children_;
  std::shared_ptr<TNode> shared_children_node_ptr_ =
      std::make_shared<TNode>(ParseStatementList());
  children_.emplace_back(shared_children_node_ptr_);
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  TNode procedure_node_(t_node_id_, TNode::Procedure, proc_name_, children_);
  return procedure_node_;
}

TNode SimpleParser::ParseStatementList() {
  std::vector<std::shared_ptr<TNode>> children_;

  do {
    std::shared_ptr<TNode> shared_children_node_ptr_ =
        std::make_shared<TNode>(ParseStatement());
    children_.emplace_back(shared_children_node_ptr_);
  } while (!MatchKind(Token::RIGHT_CURLY_BRACKET));

  t_node_id_++;
  TNode statement_list_node_(t_node_id_, TNode::StatementList, children_);
  return statement_list_node_;
}

TNode SimpleParser::ParseStatement() {
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

TNode SimpleParser::ParseAssign() {
  std::vector<std::shared_ptr<TNode>> children_;

  // Parse var name on lhs
  std::shared_ptr<TNode> shared_var_name_node_ptr_ =
      std::make_shared<TNode>(ParseVarName());
  children_.emplace_back(shared_var_name_node_ptr_);
  Expect(Token::EQUAL);

  // Parse Expr on rhs
  std::shared_ptr<TNode> shared_expr_node_ptr_ =
      std::make_shared<TNode>(ParseExpr());
  children_.emplace_back(shared_expr_node_ptr_);
  Expect(Token::SEMICOLON);

  t_node_id_++;
  TNode assign_node_(t_node_id_, TNode::Assign, statement_number_, children_);
  return assign_node_;
}

TNode SimpleParser::ParseRead() {
  Expect("read");
  std::vector<std::shared_ptr<TNode>> children_;
  std::shared_ptr<TNode> shared_var_name_node_ptr_ =
      std::make_shared<TNode>(ParseVarName());
  children_.emplace_back(shared_var_name_node_ptr_);
  Expect(Token::SEMICOLON);

  t_node_id_++;
  TNode read_node_(t_node_id_, TNode::Read, statement_number_, children_);
  return read_node_;
}

TNode SimpleParser::ParsePrint() {
  Expect("print");
  std::vector<std::shared_ptr<TNode>> children_;
  std::shared_ptr<TNode> shared_var_name_node_ptr_ =
      std::make_shared<TNode>(ParseVarName());
  children_.emplace_back(shared_var_name_node_ptr_);
  Expect(Token::SEMICOLON);

  t_node_id_++;
  TNode print_node_(t_node_id_, TNode::Print, statement_number_, children_);
  return print_node_;
}

TNode SimpleParser::ParseCall() {
  Expect("call");
  std::string proc_name_ = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);
  Expect(Token::SEMICOLON);

  t_node_id_++;
  TNode call_node_(t_node_id_, TNode::Call, statement_number_, proc_name_);
  return call_node_;
}

TNode SimpleParser::ParseWhile() {
  Expect("while");
  std::vector<std::shared_ptr<TNode>> children_;

  Expect(Token::LEFT_ROUND_BRACKET);
  std::shared_ptr<TNode> shared_cond_expr_node_ptr_ =
      std::make_shared<TNode>(ParseCondExpr());
  children_.emplace_back(shared_cond_expr_node_ptr_);
  Expect(Token::RIGHT_ROUND_BRACKET);

  Expect(Token::LEFT_CURLY_BRACKET);
  std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
      std::make_shared<TNode>(ParseStatementList());
  children_.emplace_back(shared_stmt_list_node_ptr_);
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  TNode while_node_(t_node_id_, TNode::While, statement_number_, children_);
  return while_node_;
}

TNode SimpleParser::ParseIf() {
  Expect("if");
  std::vector<std::shared_ptr<TNode>> children_;

  // Parse condition
  Expect(Token::LEFT_ROUND_BRACKET);
  std::shared_ptr<TNode> shared_cond_expr_node_ptr_ =
      std::make_shared<TNode>(ParseCondExpr());
  children_.emplace_back(shared_cond_expr_node_ptr_);
  Expect(Token::RIGHT_ROUND_BRACKET);

  // Parse 'then' statement list
  Expect(Token::LEFT_CURLY_BRACKET);
  std::shared_ptr<TNode> shared_then_stmt_list_node_ptr_ =
      std::make_shared<TNode>(ParseStatementList());
  children_.emplace_back(shared_then_stmt_list_node_ptr_);
  Expect(Token::RIGHT_CURLY_BRACKET);

  // Parse 'else' statement list
  Expect("else");
  Expect(Token::LEFT_CURLY_BRACKET);
  std::shared_ptr<TNode> shared_else_stmt_list_node_ptr_ =
      std::make_shared<TNode>(ParseStatementList());
  children_.emplace_back(shared_else_stmt_list_node_ptr_);
  Expect(Token::RIGHT_CURLY_BRACKET);

  t_node_id_++;
  TNode if_node_(t_node_id_, TNode::IfElseThen, statement_number_, children_);
  return if_node_;
}

TNode SimpleParser::ParseCondExpr() {
  // rel_expr | '!' '(' cond_expr ')' |
  // '(' cond_expr ')' '&&' '(' cond_expr ')' |
  // '(' cond_expr ')' '||' '(' cond_expr ')'

  // Check for empty condition
  if (MatchKind(Token::RIGHT_ROUND_BRACKET)) {
    throw std::runtime_error("Empty condition!");
  }

  if (MatchKind(Token::NOT)) {
    // '!' '(' cond_expr ')'
    Expect(Token::NOT);
    std::vector<std::shared_ptr<TNode>> children_;

    Expect(Token::LEFT_ROUND_BRACKET);
    std::shared_ptr<TNode> shared_cond_expr_node_ptr_ =
        std::make_shared<TNode>(ParseCondExpr());
    children_.emplace_back(shared_cond_expr_node_ptr_);
    Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    TNode not_node_(t_node_id_, TNode::Not, statement_number_, children_);
    return not_node_;
  } else if (MatchKind(Token::LEFT_ROUND_BRACKET)) {
    // '(' cond_expr ')' '&&' '(' cond_expr ')' |
    // '(' cond_expr ')' '||' '(' cond_expr ')'
    std::vector<std::shared_ptr<TNode>> children_;

    Expect(Token::LEFT_ROUND_BRACKET);
    std::shared_ptr<TNode> shared_lhs_cond_expr_node_ptr_ =
        std::make_shared<TNode>(ParseCondExpr());
    children_.emplace_back(shared_lhs_cond_expr_node_ptr_);
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
    std::shared_ptr<TNode> shared_rhs_cond_expr_node_ptr_ =
        std::make_shared<TNode>(ParseCondExpr());
    children_.emplace_back(shared_rhs_cond_expr_node_ptr_);
    Expect(Token::RIGHT_ROUND_BRACKET);

    t_node_id_++;
    TNode cond_node_(t_node_id_, type, statement_number_, children_);
    return cond_node_;
  } else {
    // rel_expr
    return ParseRelExpr();
  }
}

TNode SimpleParser::ParseRelExpr() {
  // rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
  // rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
  // rel_factor '==' rel_factor | rel_factor '!=' rel_factor
  std::vector<std::shared_ptr<TNode>> children_;
  std::shared_ptr<TNode> shared_lhs_rel_factor_node_ptr_ =
      std::make_shared<TNode>(ParseRelFactor());
  children_.emplace_back(shared_lhs_rel_factor_node_ptr_);

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

  std::shared_ptr<TNode> shared_rhs_rel_factor_node_ptr_ =
      std::make_shared<TNode>(ParseRelFactor());
  children_.emplace_back(shared_rhs_rel_factor_node_ptr_);

  t_node_id_++;
  TNode rel_expr_node_(t_node_id_, type, statement_number_, children_);
  return rel_expr_node_;
}

TNode SimpleParser::ParseRelFactor() {
  // var_name | const_value | expr
  return ParseExpr();
}

TNode SimpleParser::ParseExpr() {
  // expr '+' term | expr '-' term | term
  TNode expr_node_ = ParseTerm();
  while (!MatchKind(Token::END) &&
         ((MatchKind(Token::PLUS)) || MatchKind(Token::MINUS))) {
    std::vector<std::shared_ptr<TNode>> children_;

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

    std::shared_ptr<TNode> shared_lhs_node_ptr_ =
        std::make_shared<TNode>(expr_node_);
    children_.emplace_back(shared_lhs_node_ptr_);

    std::shared_ptr<TNode> shared_rhs_node_ptr_ =
        std::make_shared<TNode>(ParseTerm());
    children_.emplace_back(shared_rhs_node_ptr_);

    t_node_id_++;
    TNode new_expr_node_(t_node_id_, type, statement_number_, children_);

    expr_node_ = new_expr_node_;
  }
  return expr_node_;
}

TNode SimpleParser::ParseTerm() {
  // term '*' factor | term '/' factor | term '%' factor | factor
  TNode term_node_ = ParseFactor();
  while (!MatchKind(Token::END) &&
         ((MatchKind(Token::ASTERISK)) || MatchKind(Token::SLASH) ||
          MatchKind(Token::PERCENT))) {
    std::vector<std::shared_ptr<TNode>> children_;

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

    std::shared_ptr<TNode> shared_lhs_node_ptr_ =
        std::make_shared<TNode>(term_node_);
    children_.emplace_back(shared_lhs_node_ptr_);

    std::shared_ptr<TNode> shared_rhs_node_ptr_ =
        std::make_shared<TNode>(ParseFactor());
    children_.emplace_back(shared_rhs_node_ptr_);

    t_node_id_++;
    TNode new_term_node_(t_node_id_, type, statement_number_, children_);

    term_node_ = new_term_node_;
  }
  return term_node_;
}

TNode SimpleParser::ParseFactor() {
  // var_name | const_value | '(' expr ')'
  if (MatchKind(Token::IDENTIFIER)) {
    return ParseVarName();
  } else if (MatchKind(Token::NUMBER)) {
    return ParseConstValue();
  } else {
    Expect(Token::LEFT_ROUND_BRACKET);
    TNode factor_node_ = ParseExpr();
    Expect(Token::RIGHT_ROUND_BRACKET);
    return factor_node_;
  }
}

TNode SimpleParser::ParseVarName() {
  std::string var_name_ = Peek(token_pos_).GetValue();
  Expect(Token::IDENTIFIER);

  t_node_id_++;
  TNode name_node_(t_node_id_, TNode::Variable, statement_number_, var_name_);
  return name_node_;
}

TNode SimpleParser::ParseConstValue() {
  int const_value_ = stoi(Peek(token_pos_).GetValue());
  Expect(Token::NUMBER);

  t_node_id_++;
  TNode const_value_node_(t_node_id_, TNode::Constant, statement_number_,
                          const_value_);
  return const_value_node_;
}
