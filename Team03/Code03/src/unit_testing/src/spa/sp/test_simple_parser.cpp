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
  SimpleParser simple_parser = SimpleParser();
  SECTION("Test print statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};
    TNode res = simple_parser.Parse(tokens_);

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

    TNode invalid_node =
        TNode(6, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }
  SECTION("Test read statement") {
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "procedure"), Token(Token::IDENTIFIER, "main"),
        Token(Token::LEFT_CURLY_BRACKET),      Token(Token::IDENTIFIER, "read"),
        Token(Token::IDENTIFIER, "x"),         Token(Token::SEMICOLON),
        Token(Token::RIGHT_CURLY_BRACKET),     Token(Token::END)};
    TNode res = simple_parser.Parse(tokens_);

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

    TNode invalid_node =
        TNode(6, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test call statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "call"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser.Parse(tokens_);

    TNode call_node = TNode(1, TNode::Call, 1, "x");

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_ =
        std::make_shared<TNode>(call_node);
    TNode stmt_list_node =
        TNode(2, TNode::StatementList, {shared_stmt_list_node_ptr_});

    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(3, TNode::Procedure, "main", {shared_procedure_node_ptr_});

    // Next Procedure
    TNode variable_x_node = TNode(1, TNode::Variable, 2, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 2, {shared_print_node_ptr_});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_2 =
        std::make_shared<TNode>(print_node);
    TNode stmt_list_node2 =
        TNode(3, TNode::StatementList, {shared_stmt_list_node_ptr_2});

    std::shared_ptr<TNode> shared_procedure_node_ptr_2 =
        std::make_shared<TNode>(stmt_list_node2);
    TNode procedure_node2 =
        TNode(4, TNode::Procedure, "x", {shared_procedure_node_ptr_2});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    std::shared_ptr<TNode> shared_program_node_ptr_2 =
        std::make_shared<TNode>(procedure_node2);
    TNode program_node =
        TNode(4, TNode::Program,
              {shared_program_node_ptr_, shared_program_node_ptr_2});

    TNode invalid_node =
        TNode(5, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

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
                                  Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};
    TNode res = simple_parser.Parse(tokens_);

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

    // Procedure x
    TNode print_variable_x_node2 = TNode(1, TNode::Variable, 4, "x");

    std::shared_ptr<TNode> shared_print_node_ptr_2 =
        std::make_shared<TNode>(print_variable_x_node2);
    TNode print_node2 = TNode(2, TNode::Print, 4, {shared_print_node_ptr_2});

    std::shared_ptr<TNode> shared_stmt_list_print_node_ptr_2 =
        std::make_shared<TNode>(print_node2);

    TNode stmt_list_node2 =
        TNode(6, TNode::StatementList, {shared_stmt_list_print_node_ptr_2});

    std::shared_ptr<TNode> shared_procedure_node_ptr_2 =
        std::make_shared<TNode>(stmt_list_node2);
    TNode procedure_node2 =
        TNode(7, TNode::Procedure, "x", {shared_procedure_node_ptr_2});

    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node);
    std::shared_ptr<TNode> shared_program_node_ptr_2 =
        std::make_shared<TNode>(procedure_node2);

    TNode program_node =
        TNode(8, TNode::Program,
              {shared_program_node_ptr_, shared_program_node_ptr_2});

    TNode invalid_node =
        TNode(9, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

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

    TNode res = simple_parser.Parse(tokens_);

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

    TNode invalid_node =
        TNode(9, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

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

    TNode res = simple_parser.Parse(tokens_);

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
                                  Token(Token::IDENTIFIER, "then"),
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

    TNode res = simple_parser.Parse(tokens_);

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

    TNode invalid_node =
        TNode(14, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test multiple procedures with print and read statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "second"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "read"),
                                  Token(Token::IDENTIFIER, "y"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};
    TNode res = simple_parser.Parse(tokens_);

    TNode variable_x_node = TNode(1, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> shared_print_node_ptr =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 1, {shared_print_node_ptr});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr =
        std::make_shared<TNode>(print_node);
    TNode stmt_list_node =
        TNode(3, TNode::StatementList, {shared_stmt_list_node_ptr});

    std::shared_ptr<TNode> shared_procedure_node_ptr =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(4, TNode::Procedure, "main", {shared_procedure_node_ptr});

    // NEXT PROCEDURE
    TNode variable_y_node = TNode(5, TNode::Variable, 2, "y");

    std::shared_ptr<TNode> shared_print_node_ptr_2 =
        std::make_shared<TNode>(variable_y_node);
    TNode print_node_2 = TNode(6, TNode::Read, 2, {shared_print_node_ptr_2});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr_2 =
        std::make_shared<TNode>(print_node_2);
    TNode stmt_list_node_2 =
        TNode(7, TNode::StatementList, {shared_stmt_list_node_ptr_2});

    std::shared_ptr<TNode> shared_procedure_node_ptr_2 =
        std::make_shared<TNode>(stmt_list_node_2);
    TNode procedure_node_2 =
        TNode(8, TNode::Procedure, "second", {shared_procedure_node_ptr_2});

    std::shared_ptr<TNode> shared_program_node_ptr =
        std::make_shared<TNode>(procedure_node);
    std::shared_ptr<TNode> shared_program_node_ptr_2 =
        std::make_shared<TNode>(procedure_node_2);
    TNode program_node =
        TNode(9, TNode::Program,
              {shared_program_node_ptr, shared_program_node_ptr_2});

    TNode invalid_node =
        TNode(10, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test while condition ((x == 0) && (y >= 0)) with print x") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "while"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::DOUBLE_EQUAL),
                                  Token(Token::NUMBER, "0"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::AND),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "y"),
                                  Token(Token::GREATER_THAN_OR_EQUAL),
                                  Token(Token::NUMBER, "0"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser.Parse(tokens_);

    TNode variable_x_node = TNode(1, TNode::Variable, 2, "x");

    std::shared_ptr<TNode> variable_x_node_ptr =
        std::make_shared<TNode>(variable_x_node);
    TNode print_node = TNode(2, TNode::Print, 2, {variable_x_node_ptr});

    std::shared_ptr<TNode> print_node_ptr = std::make_shared<TNode>(print_node);
    TNode while_stmt_list_node =
        TNode(3, TNode::StatementList, {print_node_ptr});

    // WHILE X CONDITION NODE
    TNode cond_variable_x_node = TNode(4, TNode::Variable, 1, "x");

    TNode cond_const_node = TNode(5, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr =
        std::make_shared<TNode>(cond_variable_x_node);

    std::shared_ptr<TNode> cond_const_node_ptr =
        std::make_shared<TNode>(cond_const_node);

    TNode x_not_eq_node = TNode(6, TNode::Equal, 1,
                                {cond_variable_node_ptr, cond_const_node_ptr});

    // WHILE Y CONDITION NODE
    TNode cond_variable_y_node = TNode(7, TNode::Variable, 1, "y");

    TNode cond_y_const_node = TNode(8, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_y_node_ptr =
        std::make_shared<TNode>(cond_variable_y_node);

    std::shared_ptr<TNode> cond_y_const_node_ptr =
        std::make_shared<TNode>(cond_y_const_node);

    TNode y_not_eq_node =
        TNode(9, TNode::GreaterThanEqual, 1,
              {cond_variable_y_node_ptr, cond_y_const_node_ptr});

    // AND NODE
    std::shared_ptr<TNode> while_cond_x_node_ptr =
        std::make_shared<TNode>(x_not_eq_node);
    std::shared_ptr<TNode> while_cond_y_node_ptr =
        std::make_shared<TNode>(y_not_eq_node);
    TNode and_node = TNode(10, TNode::And, 1,
                           {while_cond_x_node_ptr, while_cond_y_node_ptr});
    // WHILE NODE
    std::shared_ptr<TNode> while_stmt_list_ptr =
        std::make_shared<TNode>(while_stmt_list_node);
    std::shared_ptr<TNode> while_and_ptr = std::make_shared<TNode>(and_node);
    TNode while_node =
        TNode(11, TNode::While, 1, {while_and_ptr, while_stmt_list_ptr});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr =
        std::make_shared<TNode>(while_node);
    TNode stmt_list_node =
        TNode(12, TNode::StatementList, {shared_stmt_list_node_ptr});

    std::shared_ptr<TNode> shared_procedure_node_ptr =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(13, TNode::Procedure, "main", {shared_procedure_node_ptr});

    std::shared_ptr<TNode> shared_program_node_ptr =
        std::make_shared<TNode>(procedure_node);
    TNode program_node(14, TNode::Program, {shared_program_node_ptr});

    TNode invalid_node(15, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test assign statement z = x * x + y * y") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "z"),
                                  Token(Token::EQUAL),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::ASTERISK),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::PLUS),
                                  Token(Token::IDENTIFIER, "y"),
                                  Token(Token::ASTERISK),
                                  Token(Token::IDENTIFIER, "y"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET),
                                  Token(Token::END)};

    TNode res = simple_parser.Parse(tokens_);

    // x times x node
    TNode first_x_node = TNode(1, TNode::Variable, 1, "x");
    TNode second_x_node = TNode(2, TNode::Variable, 1, "x");

    std::shared_ptr<TNode> first_x_node_ptr =
        std::make_shared<TNode>(first_x_node);
    std::shared_ptr<TNode> second_x_node_ptr =
        std::make_shared<TNode>(second_x_node);

    TNode x_times_node =
        TNode(3, TNode::Multiply, 1, {first_x_node_ptr, second_x_node_ptr});

    // y times y node
    TNode first_y_node = TNode(4, TNode::Variable, 1, "y");
    TNode second_y_node = TNode(5, TNode::Variable, 1, "y");

    std::shared_ptr<TNode> first_y_node_ptr =
        std::make_shared<TNode>(first_y_node);
    std::shared_ptr<TNode> second_y_node_ptr =
        std::make_shared<TNode>(second_y_node);

    TNode y_times_node =
        TNode(6, TNode::Multiply, 1, {first_y_node_ptr, second_y_node_ptr});

    // PLUS NODE
    std::shared_ptr<TNode> x_times_node_ptr =
        std::make_shared<TNode>(x_times_node);
    std::shared_ptr<TNode> y_times_node_ptr =
        std::make_shared<TNode>(y_times_node);

    TNode plus_node =
        TNode(7, TNode::Plus, 1, {x_times_node_ptr, y_times_node_ptr});

    // Variable z node
    TNode z_node = TNode(8, TNode::Variable, 1, "z");

    // PLUS NODE
    std::shared_ptr<TNode> plus_node_ptr = std::make_shared<TNode>(plus_node);

    std::shared_ptr<TNode> z_node_ptr = std::make_shared<TNode>(z_node);

    TNode assign_node = TNode(9, TNode::Assign, 1, {z_node_ptr, plus_node_ptr});

    std::shared_ptr<TNode> shared_stmt_list_node_ptr =
        std::make_shared<TNode>(assign_node);
    TNode stmt_list_node =
        TNode(10, TNode::StatementList, {shared_stmt_list_node_ptr});

    std::shared_ptr<TNode> shared_procedure_node_ptr =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(11, TNode::Procedure, "main", {shared_procedure_node_ptr});

    std::shared_ptr<TNode> shared_program_node_ptr =
        std::make_shared<TNode>(procedure_node);
    TNode program_node = TNode(12, TNode::Program, {shared_program_node_ptr});

    TNode invalid_node =
        TNode(13, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test nested If-while") {
    Lexer lexer;
    std::string input =
        "procedure p { if (m == 0) then { while (n == 0) { read x; } } else { "
        "while (o == 0) { read y; } } }";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    // THEN WHILE NODE CONSTRUCTION
    // Read x node
    TNode variable_x_node = TNode(1, TNode::Variable, 3, "x");

    std::shared_ptr<TNode> variable_x_node_ptr =
        std::make_shared<TNode>(variable_x_node);
    TNode read_node = TNode(2, TNode::Read, 3, {variable_x_node_ptr});

    // Stmtlist Node
    std::shared_ptr<TNode> read_node_ptr = std::make_shared<TNode>(read_node);
    TNode while_stmt_list_node =
        TNode(3, TNode::StatementList, {read_node_ptr});

    // Then while cond node
    TNode cond_variable_node = TNode(4, TNode::Variable, 2, "n");

    TNode cond_const_node = TNode(5, TNode::Constant, 2, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr =
        std::make_shared<TNode>(cond_variable_node);

    std::shared_ptr<TNode> cond_const_node_ptr =
        std::make_shared<TNode>(cond_const_node);

    TNode eq_node = TNode(6, TNode::Equal, 2,
                          {cond_variable_node_ptr, cond_const_node_ptr});

    // THEN WHILE NODE
    std::shared_ptr<TNode> while_stmt_list_ptr =
        std::make_shared<TNode>(while_stmt_list_node);
    std::shared_ptr<TNode> while_cond_ptr = std::make_shared<TNode>(eq_node);
    TNode while_node =
        TNode(7, TNode::While, 2, {while_cond_ptr, while_stmt_list_ptr});

    // ELSE WHILE NODE CONSTRUCTION
    // Read y node
    TNode variable_y_node = TNode(8, TNode::Variable, 5, "y");

    std::shared_ptr<TNode> variable_y_node_ptr =
        std::make_shared<TNode>(variable_y_node);
    TNode read_node2 = TNode(9, TNode::Read, 5, {variable_y_node_ptr});

    // Stmtlist Node
    std::shared_ptr<TNode> read_node_ptr2 = std::make_shared<TNode>(read_node2);
    TNode while_stmt_list_node2 =
        TNode(10, TNode::StatementList, {read_node_ptr2});

    // Then while cond node
    TNode cond_variable_node2 = TNode(11, TNode::Variable, 4, "o");

    TNode cond_const_node2 = TNode(12, TNode::Constant, 4, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr2 =
        std::make_shared<TNode>(cond_variable_node2);

    std::shared_ptr<TNode> cond_const_node_ptr2 =
        std::make_shared<TNode>(cond_const_node2);

    TNode eq_node2 = TNode(13, TNode::Equal, 4,
                           {cond_variable_node_ptr2, cond_const_node_ptr2});

    // ELSE WHILE NODE
    std::shared_ptr<TNode> while_stmt_list_ptr2 =
        std::make_shared<TNode>(while_stmt_list_node2);
    std::shared_ptr<TNode> while_cond_ptr2 = std::make_shared<TNode>(eq_node2);
    TNode while_node2 =
        TNode(14, TNode::While, 4, {while_cond_ptr2, while_stmt_list_ptr2});

    // IF ELSE NODE CONSTRUCTION
    // THEN STATEMENTLIST
    std::shared_ptr<TNode> while_node_ptr = std::make_shared<TNode>(while_node);
    TNode then_stmt_list_node =
        TNode(15, TNode::StatementList, {while_node_ptr});

    // ELSE STATEMENTLIST
    std::shared_ptr<TNode> while_node_ptr2 =
        std::make_shared<TNode>(while_node2);
    TNode else_stmt_list_node =
        TNode(16, TNode::StatementList, {while_node_ptr2});

    // IF COND NODE
    TNode cond_variable_m_node = TNode(17, TNode::Variable, 1, "m");

    TNode if_const_const_node = TNode(18, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_m_node_ptr_ =
        std::make_shared<TNode>(cond_variable_m_node);

    std::shared_ptr<TNode> if_const_node_ptr_ =
        std::make_shared<TNode>(if_const_const_node);

    TNode if_cond_node = TNode(19, TNode::Equal, 1,
                               {cond_variable_m_node_ptr_, if_const_node_ptr_});

    // IF NODE
    std::shared_ptr<TNode> then_stmt_list_ptr_ =
        std::make_shared<TNode>(then_stmt_list_node);
    std::shared_ptr<TNode> else_stmt_list_ptr_ =
        std::make_shared<TNode>(else_stmt_list_node);
    std::shared_ptr<TNode> if_cond_node_ptr_ =
        std::make_shared<TNode>(if_cond_node);

    TNode if_node =
        TNode(20, TNode::IfElseThen, 1,
              {if_cond_node_ptr_, then_stmt_list_ptr_, else_stmt_list_ptr_});

    // Program Node
    std::shared_ptr<TNode> shared_stmt_list_node_ptr =
        std::make_shared<TNode>(if_node);
    TNode stmt_list_node =
        TNode(21, TNode::StatementList, {shared_stmt_list_node_ptr});

    std::shared_ptr<TNode> shared_procedure_node_ptr =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(22, TNode::Procedure, "p", {shared_procedure_node_ptr});

    std::shared_ptr<TNode> shared_program_node_ptr =
        std::make_shared<TNode>(procedure_node);
    TNode program_node(23, TNode::Program, {shared_program_node_ptr});

    TNode invalid_node(24, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }

  SECTION("Test nested While-if") {
    Lexer lexer;
    std::string input =
        "procedure p { while (m == 0) { if (n == 0) then { read x; } else { "
        "read y; } } }";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    // IF ELSE NODE CONSTRUCTION
    // Read x node
    TNode variable_x_node = TNode(1, TNode::Variable, 3, "x");

    std::shared_ptr<TNode> variable_x_node_ptr =
        std::make_shared<TNode>(variable_x_node);
    TNode read_node = TNode(2, TNode::Read, 3, {variable_x_node_ptr});

    // Then Stmtlist Node
    std::shared_ptr<TNode> read_node_ptr = std::make_shared<TNode>(read_node);
    TNode then_stmt_list_node = TNode(3, TNode::StatementList, {read_node_ptr});

    // Read y node
    TNode variable_y_node = TNode(4, TNode::Variable, 4, "y");
    std::shared_ptr<TNode> variable_y_node_ptr =
        std::make_shared<TNode>(variable_y_node);
    TNode read_node2 = TNode(5, TNode::Read, 4, {variable_y_node_ptr});

    // Else Stmtlist Node
    std::shared_ptr<TNode> read_node_ptr2 = std::make_shared<TNode>(read_node2);
    TNode else_stmt_list_node =
        TNode(6, TNode::StatementList, {read_node_ptr2});

    // If cond node
    TNode cond_variable_n_node = TNode(7, TNode::Variable, 2, "n");

    TNode if_const_const_node = TNode(8, TNode::Constant, 2, 0);

    std::shared_ptr<TNode> cond_variable_n_node_ptr_ =
        std::make_shared<TNode>(cond_variable_n_node);

    std::shared_ptr<TNode> if_const_node_ptr_ =
        std::make_shared<TNode>(if_const_const_node);

    TNode if_cond_node = TNode(9, TNode::Equal, 2,
                               {cond_variable_n_node_ptr_, if_const_node_ptr_});

    // IF NODE
    std::shared_ptr<TNode> then_stmt_list_ptr_ =
        std::make_shared<TNode>(then_stmt_list_node);
    std::shared_ptr<TNode> else_stmt_list_ptr_ =
        std::make_shared<TNode>(else_stmt_list_node);
    std::shared_ptr<TNode> if_cond_node_ptr_ =
        std::make_shared<TNode>(if_cond_node);

    TNode if_node =
        TNode(10, TNode::IfElseThen, 2,
              {if_cond_node_ptr_, then_stmt_list_ptr_, else_stmt_list_ptr_});

    // While cond node
    TNode cond_variable_node = TNode(11, TNode::Variable, 1, "m");

    TNode cond_const_node = TNode(12, TNode::Constant, 1, 0);

    std::shared_ptr<TNode> cond_variable_node_ptr =
        std::make_shared<TNode>(cond_variable_node);

    std::shared_ptr<TNode> cond_const_node_ptr =
        std::make_shared<TNode>(cond_const_node);

    TNode eq_node = TNode(13, TNode::Equal, 1,
                          {cond_variable_node_ptr, cond_const_node_ptr});

    // WHILE STATEMENTLIST NODE
    std::shared_ptr<TNode> if_node_ptr = std::make_shared<TNode>(if_node);
    TNode while_stmt_list_node = TNode(14, TNode::StatementList, {if_node_ptr});

    // WHILE NODE
    std::shared_ptr<TNode> while_stmt_list_ptr =
        std::make_shared<TNode>(while_stmt_list_node);
    std::shared_ptr<TNode> while_cond_ptr = std::make_shared<TNode>(eq_node);
    TNode while_node =
        TNode(15, TNode::While, 1, {while_cond_ptr, while_stmt_list_ptr});

    // Program Node
    std::shared_ptr<TNode> shared_stmt_list_node_ptr =
        std::make_shared<TNode>(while_node);
    TNode stmt_list_node =
        TNode(16, TNode::StatementList, {shared_stmt_list_node_ptr});

    std::shared_ptr<TNode> shared_procedure_node_ptr =
        std::make_shared<TNode>(stmt_list_node);
    TNode procedure_node =
        TNode(17, TNode::Procedure, "p", {shared_procedure_node_ptr});

    std::shared_ptr<TNode> shared_program_node_ptr =
        std::make_shared<TNode>(procedure_node);
    TNode program_node(18, TNode::Program, {shared_program_node_ptr});

    TNode invalid_node(19, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());

    REQUIRE_FALSE(deepEqual(res, invalid_node));
    REQUIRE(deepEqual(res, program_node));
  }
  SECTION("Test call non existing procedure") {
    Lexer lexer;
    std::string input = "procedure p { call q; }";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    TNode invalid_node(19, TNode::Invalid,
                       std::vector<std::shared_ptr<TNode>>());

    REQUIRE(deepEqual(res, invalid_node));
  }

  SECTION("Test cyclic call procedure") {
    Lexer lexer;
    std::string input =
        "procedure p { call q; } procedure q { call r; } procedure r { call p; "
        "}";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    TNode invalid_node =
        TNode(10, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE(deepEqual(res, invalid_node));
  }

  SECTION("Test recursive call procedure") {
    Lexer lexer;
    std::string input = "procedure p { call p; } ";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    TNode invalid_node =
        TNode(10, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE(deepEqual(res, invalid_node));
  }

  SECTION("Test same name procedures") {
    Lexer lexer;
    std::string input = "procedure p { print x; } procedure p { print y; }";
    std::vector<Token> tokens = lexer.LexLine(input);
    tokens.emplace_back(Token::END);
    TNode res = simple_parser.Parse(tokens);

    TNode invalid_node =
        TNode(10, TNode::Invalid, std::vector<std::shared_ptr<TNode>>());

    REQUIRE(deepEqual(res, invalid_node));
  }
}