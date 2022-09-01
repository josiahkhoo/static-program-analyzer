#include "catch.hpp"
#include "common/t_node.h"

TEST_CASE("Constant TNode", "[TNode]") {
  // Given
  int line_number = 1;
  int int_value = 2;
  TNode::Type type = TNode::Constant;
  // When
  TNode constant_node = TNode(0, type, line_number, int_value);

  SECTION("Is Leaf") { REQUIRE(constant_node.IsLeaf()); }
  SECTION("Is Type") { REQUIRE(constant_node.IsType(type)); }
  SECTION("Get Int Value") {
    REQUIRE(constant_node.GetIntValue() == int_value);
  }
  SECTION("Get Line Number") {
    REQUIRE(constant_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") { REQUIRE_FALSE(constant_node.IsNotType(type)); }
}

TEST_CASE("Variable TNode", "[TNode]") {
  // Given
  int line_number = 1;
  std::string name = "a";
  TNode::Type type = TNode::Variable;
  // When
  TNode variable_node = TNode(0, type, line_number, name);
  // Then
  SECTION("Is Leaf") { REQUIRE(variable_node.IsLeaf()); }
  SECTION("Is Type") { REQUIRE(variable_node.IsType(type)); }
  SECTION("Get String Value") {
    REQUIRE(variable_node.GetStringValue() == name);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") { REQUIRE_FALSE(variable_node.IsNotType(type)); }
}

TEST_CASE("Assign TNode", "[TNode]") {
  // Given
  int line_number = 1;
  TNode variable_node = TNode(0, TNode::Variable, 1, "a");
  TNode constant_node = TNode(0, TNode::Constant, 1, 2);
  std::vector<std::shared_ptr<TNode>> children = {
      std::make_shared<TNode>(variable_node),
      std::make_shared<TNode>(constant_node)};
  // When
  TNode assign_node = TNode(0, TNode::Assign, 1, children);
  // Then
  SECTION("Is Statement") { REQUIRE(assign_node.IsStatement()); }
  SECTION("Is Type") { REQUIRE(assign_node.IsType(TNode::Assign)); }
  SECTION("Get Children") {
    // Children are set up correctly
    REQUIRE(assign_node.GetChildren()[0] == children[0]);
    REQUIRE(assign_node.GetChildren()[1] == children[1]);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") {
    REQUIRE_FALSE(assign_node.IsNotType(TNode::Assign));
  }
}

TEST_CASE("Plus TNode", "[TNode]") {
  // Given
  int line_number = 1;
  TNode variable_node = TNode(0, TNode::Variable, 1, "a");
  TNode constant_node = TNode(0, TNode::Constant, 1, 2);
  std::vector<std::shared_ptr<TNode>> children = {
      std::make_shared<TNode>(variable_node),
      std::make_shared<TNode>(constant_node)};
  // When
  TNode assign_node = TNode(0, TNode::Plus, 1, children);
  // Then
  SECTION("Is Plus Minus Operator") {
    REQUIRE(assign_node.IsPlusMinusOperator());
  }
  SECTION("Is Type") { REQUIRE(assign_node.IsType(TNode::Plus)); }
  SECTION("Get Children") {
    // Children are set up correctly
    REQUIRE(assign_node.GetChildren()[0] == children[0]);
    REQUIRE(assign_node.GetChildren()[1] == children[1]);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") { REQUIRE_FALSE(assign_node.IsNotType(TNode::Plus)); }
}

TEST_CASE("Equals TNode", "[TNode]") {
  // Given
  int line_number = 1;
  TNode variable_node = TNode(0, TNode::Variable, 1, "a");
  TNode constant_node = TNode(0, TNode::Constant, 1, 2);
  std::vector<std::shared_ptr<TNode>> children = {
      std::make_shared<TNode>(variable_node),
      std::make_shared<TNode>(constant_node)};
  // When
  TNode assign_node = TNode(0, TNode::Equal, 1, children);
  // Then
  SECTION("Is Equal Operator") { REQUIRE(assign_node.IsEqualityOperator()); }
  SECTION("Is Type") { REQUIRE(assign_node.IsType(TNode::Equal)); }
  SECTION("Get Children") {
    // Children are set up correctly
    REQUIRE(assign_node.GetChildren()[0] == children[0]);
    REQUIRE(assign_node.GetChildren()[1] == children[1]);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") { REQUIRE_FALSE(assign_node.IsNotType(TNode::Equal)); }
}

TEST_CASE("Multiply TNode", "[TNode]") {
  // Given
  int line_number = 1;
  TNode variable_node = TNode(0, TNode::Variable, 1, "a");
  TNode constant_node = TNode(0, TNode::Constant, 1, 2);
  std::vector<std::shared_ptr<TNode>> children = {
      std::make_shared<TNode>(variable_node),
      std::make_shared<TNode>(constant_node)};
  // When
  TNode assign_node = TNode(0, TNode::Multiply, 1, children);
  // Then
  SECTION("Is Times Divide Quotient Operator") {
    REQUIRE(assign_node.IsTimesDivideQuotientOperator());
  }
  SECTION("Is Type") { REQUIRE(assign_node.IsType(TNode::Multiply)); }
  SECTION("Get Children") {
    // Children are set up correctly
    REQUIRE(assign_node.GetChildren()[0] == children[0]);
    REQUIRE(assign_node.GetChildren()[1] == children[1]);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") {
    REQUIRE_FALSE(assign_node.IsNotType(TNode::Multiply));
  }
}

TEST_CASE("And TNode", "[TNode]") {
  // Given
  int line_number = 1;
  TNode variable_node =
      TNode(0, TNode::Equal, 1, std::vector<std::shared_ptr<TNode>>());
  TNode constant_node =
      TNode(0, TNode::Equal, 1, std::vector<std::shared_ptr<TNode>>());
  std::vector<std::shared_ptr<TNode>> children = {
      std::make_shared<TNode>(variable_node),
      std::make_shared<TNode>(constant_node)};
  // When
  TNode assign_node = TNode(0, TNode::And, 1, children);
  // Then
  SECTION("Is Logical Operator") { REQUIRE(assign_node.IsLogicalOperator()); }
  SECTION("Is Type") { REQUIRE(assign_node.IsType(TNode::And)); }
  SECTION("Get Children") {
    // Children are set up correctly
    REQUIRE(assign_node.GetChildren()[0] == children[0]);
    REQUIRE(assign_node.GetChildren()[1] == children[1]);
  }
  SECTION("Get Line Number") {
    REQUIRE(variable_node.GetStatementNumber() == line_number);
  }
  SECTION("Is Not Type") { REQUIRE_FALSE(assign_node.IsNotType(TNode::And)); }
}