#include <iostream>

#include "catch.hpp"
#include "sp/simple_parser.h"

bool deepEqual(TNode node1, TNode node2);

bool deepEqual(TNode node1, TNode node2) {
  if (node1 != node2) {
    return false;
  }
  if (node1.GetChildren().size() != node2.GetChildren().size()) {
    return false;
  }
  for (int i = 0; i < node1.GetChildren().size(); i++) {
    if (!deepEqual(*node1.GetChildren()[i], *node2.GetChildren()[i])) {
      return false;
    }
  }
  return true;
}

TEST_CASE("Simple Parser", "[Simple Parser]") {
  SimpleParser simple_parser_ = SimpleParser();
  SECTION("Test print statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};
    TNode res = simple_parser_.Parse(tokens_);

    TNode variable_x_node_ = TNode(0, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(variable_x_node_);
    TNode print_node_ = TNode(0, TNode::Print, 1, {shared_print_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(print_node_);
    TNode stmt_list_node_ =
        TNode(0, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node_);
    TNode procedure_node_ =
        TNode(0, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    TNode program_node_(0, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node_));
    REQUIRE(deepEqual(res, program_node_));
  }
  SECTION("Test read statement") {
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "procedure"), Token(Token::IDENTIFIER, "main"),
        Token(Token::LEFT_CURLY_BRACKET),      Token(Token::IDENTIFIER, "read"),
        Token(Token::IDENTIFIER, "x"),         Token(Token::SEMICOLON),
        Token(Token::RIGHT_CURLY_BRACKET),     Token(Token::END)};
    TNode res = simple_parser_.Parse(tokens_);

    TNode variable_x_node_ = TNode(0, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_read_node_ptr_ =
        std::make_shared<TNode>(variable_x_node_);
    TNode read_node_ = TNode(0, TNode::Read, 1, {shared_read_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(read_node_);
    TNode stmt_list_node_ =
        TNode(0, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node_);
    TNode procedure_node_ =
        TNode(0, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    TNode program_node_(0, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node_));
    REQUIRE(deepEqual(res, program_node_));
  }

  SECTION("Test call statement") {
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "procedure"), Token(Token::IDENTIFIER, "main"),
        Token(Token::LEFT_CURLY_BRACKET),      Token(Token::IDENTIFIER, "call"),
        Token(Token::IDENTIFIER, "x"),         Token(Token::SEMICOLON),
        Token(Token::RIGHT_CURLY_BRACKET),     Token(Token::END)};

    TNode res = simple_parser_.Parse(tokens_);

    TNode call_node_ = TNode(0, TNode::Call, 1, "x");

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(call_node_);
    TNode stmt_list_node_ =
        TNode(0, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node_);
    TNode procedure_node_ =
        TNode(0, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    TNode program_node_(0, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node_));
    REQUIRE(deepEqual(res, program_node_));
  }

  SECTION("Test print,call and read statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "call"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "read"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};
    TNode res = simple_parser_.Parse(tokens_);

    TNode print_variable_x_node_ = TNode(0, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(print_variable_x_node_);
    TNode print_node_ = TNode(0, TNode::Print, 1, {shared_print_node_ptr_});

    TNode call_node_ = TNode(0, TNode::Call, 2, "x");

    TNode read_variable_x_node_ = TNode(0, TNode::Variable, 3, "x");

    std::shared_ptr<TNode> shared_read_node_ptr_ =
        std::make_shared<TNode>(read_variable_x_node_);
    TNode read_node_ = TNode(0, TNode::Read, 3, {shared_read_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_print_node_ptr_ =
        std::make_shared<TNode>(print_node_);

    std::shared_ptr<TNode> shared_stmt_list_call_node_ptr_ =
        std::make_shared<TNode>(call_node_);

    std::shared_ptr<TNode> shared_stmt_list_read_node_ptr_ =
        std::make_shared<TNode>(read_node_);

    TNode stmt_list_node_ = TNode(
        0, TNode::StatementList,
        {shared_stmt_list_print_node_ptr_, shared_stmt_list_call_node_ptr_,
         shared_stmt_list_read_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node_);
    TNode procedure_node_ =
        TNode(0, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    TNode program_node_(0, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node_));
    REQUIRE(deepEqual(res, program_node_));
  }
  SECTION("Test assign statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::EQUAL),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::PLUS),
                                  Token(Token::NUMBER, "1"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser_.Parse(tokens_);

    TNode rhs_var_node_ = TNode(0, TNode::Variable, 1, "x");
    std::shared_ptr<TNode> lhs_plus_var_node_ptr_ =
        std::make_shared<TNode>(rhs_var_node_);
    TNode const_node_ = TNode(0, TNode::Constant, 1, 1);
    std::shared_ptr<TNode> rhs_const_node_ptr_ =
        std::make_shared<TNode>(const_node_);
    TNode plus_node_ =
        TNode(0, TNode::Plus, 1, {lhs_plus_var_node_ptr_, rhs_const_node_ptr_});

    TNode lhs_var_node_ = TNode(0, TNode::Variable, 1, "x");
    std::shared_ptr<TNode> lhs_node_ptr_ =
        std::make_shared<TNode>(lhs_var_node_);
    std::shared_ptr<TNode> plus_node_ptr_ = std::make_shared<TNode>(plus_node_);
    TNode assign_node_ =
        TNode(0, TNode::Assign, 1, {lhs_node_ptr_, plus_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(assign_node_);
    TNode stmt_list_node_ =
        TNode(0, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node_);
    TNode procedure_node_ =
        TNode(0, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    TNode program_node_(0, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node_(0, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node_));
    REQUIRE(deepEqual(res, program_node_));
  }
}