#include "catch.hpp"
#include "sp/simple_parser.h"

TEST_CASE("Simple Parser", "[Simple Parser]") {
  SimpleParser simple_parser_ = SimpleParser();
  SECTION("Test print statement") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "main"),
                                  Token(Token::LEFT_CURLY_BRACKET),
                                  Token(Token::IDENTIFIER, "print"),
                                  Token(Token::IDENTIFIER, "x"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::RIGHT_CURLY_BRACKET)
                                  };
    TNode res = simple_parser_.Parse(tokens_);

    TNode variable_x_node_ = TNode(TNode::Variable, 1, "x");

    std::vector<std::shared_ptr<TNode>> print_node_children_;
    std::shared_ptr<TNode> shared_print_node_ptr_ =
        std::make_shared<TNode>(variable_x_node_);
    print_node_children_.emplace_back(shared_print_node_ptr_);
    TNode print_node_ = TNode(TNode::Print, 1, print_node_children_);

    std::vector<std::shared_ptr<TNode>> procedure_node_children_;
    std::shared_ptr<TNode> shared_procedure_node_ptr_ =
        std::make_shared<TNode>(print_node_);
    procedure_node_children_.emplace_back(shared_procedure_node_ptr_);
    TNode procedure_node_ = TNode(TNode::Procedure, 0, "main", procedure_node_children_);

    std::vector<std::shared_ptr<TNode>> program_node_children_;
    std::shared_ptr<TNode> shared_program_node_ptr_ =
        std::make_shared<TNode>(procedure_node_);
    program_node_children_.emplace_back(shared_program_node_ptr_);
    TNode program_node_(TNode::Program, 0, program_node_children_);

    
    TNode
    REQUIRE()
  }
}