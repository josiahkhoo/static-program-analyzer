#include <iostream>

#include "catch.hpp"
#include "sp/simple_parser.h"

bool deepEqual(TNode node1, TNode node2);

bool deepEqual(TNode node1, TNode node2) {
  //  if (node1.GetType() == TNode::Program && node2.GetType() ==
  //  TNode::Program) {
  //    std::cout << "Pass Program\n";
  //  }
  //  if (node1.GetType() == TNode::Procedure && node2.GetType() ==
  //  TNode::Procedure) {
  //    std::cout << "Pass Procedure\n";
  //  }
  //  if (node1.GetType() == TNode::StatementList && node2.GetType() ==
  //  TNode::StatementList) {
  //    std::cout << "Pass StatementList\n";
  //  }
  //  if (node1.GetType() == TNode::IfElseThen && node2.GetType() ==
  //  TNode::IfElseThen) {
  //    std::cout << "Pass If\n";
  //  }
  //  if (node1.GetType() == TNode::NotEqual && node2.GetType() ==
  //  TNode::NotEqual) {
  //    std::cout << "Pass NotEqual\n";
  //  }
  //  if (node1.GetType() == TNode::Variable && node2.GetType() ==
  //  TNode::Variable) {
  //    std::cout << "Pass Variable\n";
  //  }
  //  if (node1.GetType() == TNode::Constant && node2.GetType() ==
  //  TNode::Constant) {
  //    std::cout << "Pass Constant\n";
  //  }
  //  if (node1.GetType() == TNode::Print && node2.GetType() == TNode::Print) {
  //    std::cout << "Pass Print\n";
  //  }
  //
  //  if (node1.GetType() == TNode::Read && node2.GetType() == TNode::Read) {
  //    std::cout << "Pass Read\n";
  //  }

  if (node1 != node2) {
    // std::cout << "not equal node\n";
    return false;
  }
  if (node1.GetChildren().size() != node2.GetChildren().size()) {
    // std::cout << "children size not equal\n";
    return false;
  }
  for (int i = 0; i < node1.GetChildren().size(); i++) {
    // std::cout << "checking children\n";
    if (!deepEqual(*node1.GetChildren()[i], *node2.GetChildren()[i])) {
      // std::cout << "children not equal\n";
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

    TNode variable_x_node = TNode(1, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 1, {shared_print_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(print_node);
    TNode stmt_list_node =
        TNode(3, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(4, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(5, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(6, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }
  SECTION("Test read statement") {
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "procedure"), Token(Token::IDENTIFIER, "main"),
        Token(Token::LEFT_CURLY_BRACKET),      Token(Token::IDENTIFIER, "read"),
        Token(Token::IDENTIFIER, "x"),         Token(Token::SEMICOLON),
        Token(Token::RIGHT_CURLY_BRACKET),     Token(Token::END)};
    TNode res = simple_parser_.Parse(tokens_);

    TNode variable_x_node = TNode(1, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_read_node_ptr_ =
        std::make_shared<TNode>(variable_x_node);
    TNode read_node = TNode(2, TNode::Read, 1, {shared_read_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(read_node);
    TNode stmt_list_node =
        TNode(3, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(4, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(5, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(6, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test call statement") {
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "procedure"), Token(Token::IDENTIFIER, "main"),
        Token(Token::LEFT_CURLY_BRACKET),      Token(Token::IDENTIFIER, "call"),
        Token(Token::IDENTIFIER, "x"),         Token(Token::SEMICOLON),
        Token(Token::RIGHT_CURLY_BRACKET),     Token(Token::END)};

    TNode res = simple_parser_.Parse(tokens_);

    TNode call_node = TNode(1, TNode::Call, 1, "x");

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(call_node);
    TNode stmt_list_node =
        TNode(2, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(3, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(4, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(5, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
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

    TNode print_variable_x_node = TNode(1, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(print_variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 1, {shared_print_node_ptr_});

    TNode call_node = TNode(3, TNode::Call, 2, "x");

    TNode read_variable_x_node = TNode(4, TNode::Variable, 3, "x");

    std::shared_ptr<TNode> shared_read_node_ptr_ =
        std::make_shared<TNode>(read_variable_x_node);
    TNode read_node = TNode(5, TNode::Read, 3, {shared_read_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_print_node_ptr_ =
        std::make_shared<TNode>(print_node);

    std::shared_ptr<TNode> shared_stmt_list_call_node_ptr_ =
        std::make_shared<TNode>(call_node);

    std::shared_ptr<TNode> shared_stmt_list_read_node_ptr_ =
        std::make_shared<TNode>(read_node);

    TNode stmt_list_node = TNode(
        6, TNode::StatementList,
        {shared_stmt_list_print_node_ptr_, shared_stmt_list_call_node_ptr_,
         shared_stmt_list_read_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(7, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(8, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(9, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }
  SECTION("Test assign statement x = x + 1;") {
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

    TNode rhs_var_node = TNode(1, TNode::Variable, 1, "x");
    std::shared_ptr<TNode> lhs_plus_var_node_ptr_ =
        std::make_shared<TNode>(rhs_var_node);
    TNode const_node_ = TNode(2, TNode::Constant, 1, 1);
    std::shared_ptr<TNode> rhs_const_node_ptr_ =
        std::make_shared<TNode>(const_node_);
    TNode plus_node =
        TNode(3, TNode::Plus, 1, {lhs_plus_var_node_ptr_, rhs_const_node_ptr_});

    TNode lhs_var_node = TNode(4, TNode::Variable, 1, "x");
    std::shared_ptr<TNode> lhs_node_ptr_ =
        std::make_shared<TNode>(lhs_var_node);
    std::shared_ptr<TNode> plus_node_ptr_ = std::make_shared<TNode>(plus_node);
    TNode assign_node =
        TNode(5, TNode::Assign, 1, {lhs_node_ptr_, plus_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(assign_node);
    TNode stmt_list_node =
        TNode(6, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(7, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(8, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(9, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test while statement with print x;") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "while"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::NOT_EQUAL),
                                  Token(Token::NUMBER, "0"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser_.Parse(tokens_);

    TNode variable_x_node = TNode(1, TNode::Variable, 2, "x");

    std::shared_ptr<TNode> variable_x_node_ptr_ =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 2, {variable_x_node_ptr_});

    std::shared_ptr<TNode> print_node_ptr_ =
        std::make_shared<TNode>(print_node);
    TNode while_stmt_list_node =
        TNode(3, TNode::StatementList, {print_node_ptr_});

    // WHILE CONDITION NODE
    TNode cond_variable_x_node = TNode(4, TNode::Variable, 1, "x");

    TNode cond_const_node = TNode(5, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr_ =
        std::make_shared<TNode>(cond_variable_x_node);

    std::shared_ptr<TNode> cond_const_node_ptr_ =
        std::make_shared<TNode>(cond_const_node);

    TNode not_eq_node = TNode(6, TNode::NotEqual, 1,
                               {cond_variable_node_ptr_, cond_const_node_ptr_});

    // WHILE NODE
    std::shared_ptr<TNode> while_stmt_list_ptr_ =
        std::make_shared<TNode>(while_stmt_list_node);
    std::shared_ptr<TNode> while_cond_node_ptr_ =
        std::make_shared<TNode>(not_eq_node);

    TNode while_node =
        TNode(7, TNode::While, 1, {while_cond_node_ptr_, while_stmt_list_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(while_node);
    TNode stmt_list_node =
        TNode(8, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(9, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node(10, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node(11, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test if statement with print x;") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "if"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::NOT_EQUAL),
                                  Token(Token::NUMBER, "0"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "else"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "read"),
                                  Token(Token::IDENTIFIER, "y"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser_.Parse(tokens_);

    // THEN STATEMENT LIST
    TNode variable_x_node = TNode(1, TNode::Variable, 2, "x");

    std::shared_ptr<TNode> variable_x_node_ptr_ =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 2, {variable_x_node_ptr_});

    std::shared_ptr<TNode> print_node_ptr_ =
        std::make_shared<TNode>(print_node);
    TNode then_stmt_list_node =
        TNode(3, TNode::StatementList, {print_node_ptr_});

    // ELSE STATEMENT LIST
    TNode variable_y_node = TNode(4, TNode::Variable, 3, "y");

    std::shared_ptr<TNode> variable_y_node_ptr_ =
        std::make_shared<TNode>(variable_y_node);
    TNode read_node = TNode(5, TNode::Read, 3, {variable_y_node_ptr_});

    std::shared_ptr<TNode> read_node_ptr_ = std::make_shared<TNode>(read_node);
    TNode else_stmt_list_node =
        TNode(6, TNode::StatementList, {read_node_ptr_});

    // IF CONDITION NODE
    TNode cond_variable_x_node = TNode(7, TNode::Variable, 1, "x");

    TNode cond_const_node = TNode(8, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr_ =
        std::make_shared<TNode>(cond_variable_x_node);

    std::shared_ptr<TNode> cond_const_node_ptr_ =
        std::make_shared<TNode>(cond_const_node);

    TNode not_eq_node = TNode(9, TNode::NotEqual, 1,
                               {cond_variable_node_ptr_, cond_const_node_ptr_});

    // IF NODE
    std::shared_ptr<TNode> then_stmt_list_ptr_ =
        std::make_shared<TNode>(then_stmt_list_node);
    std::shared_ptr<TNode> else_stmt_list_ptr_ =
        std::make_shared<TNode>(else_stmt_list_node);
    std::shared_ptr<TNode> if_cond_node_ptr_ =
        std::make_shared<TNode>(not_eq_node);

    TNode if_node =
        TNode(10, TNode::IfElseThen, 1,
              {if_cond_node_ptr_, then_stmt_list_ptr_, else_stmt_list_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(if_node);
    TNode stmt_list_node =
        TNode(11, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(12, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(13, TNode::Program, {shared_program_node_ptr_});

    TNode invalid_node = TNode(14, TNode::Invalid,
                        std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }
}