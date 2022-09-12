#include "catch.hpp"
#include "common/entity/assign_entity.h"
#include "common/t_node.h"

TEST_CASE("Assign Entity", "[AssignEntity]") {
  SECTION("x = 1 + y") {
    int statement_number = 1;
    TNode one = TNode(1, TNode::Constant, statement_number, 1);
    TNode y = TNode(2, TNode::Variable, statement_number, "y");
    TNode plus =
        TNode(3, TNode::Plus, statement_number,
              {std::make_shared<TNode>(one), std::make_shared<TNode>(y)});
    TNode x = TNode(4, TNode::Variable, 1, "x");
    TNode assign =
        TNode(5, TNode::Assign, statement_number,
              {std::make_shared<TNode>(x), std::make_shared<TNode>(plus)});
    AssignEntity assign_entity = AssignEntity(assign, statement_number);

    REQUIRE(assign_entity.GetLeftHandSidePattern() == "x");
    REQUIRE(assign_entity.GetRightHandSidePattern() == "((1)+(y))");
  }

  SECTION("x = 1 - y * z") {
    int statement_number = 1;
    TNode one = TNode(1, TNode::Constant, statement_number, 1);
    TNode y = TNode(2, TNode::Variable, statement_number, "y");
    TNode z = TNode(3, TNode::Variable, statement_number, "z");
    TNode times =
        TNode(4, TNode::Multiply, statement_number,
              {std::make_shared<TNode>(y), std::make_shared<TNode>(z)});
    TNode minus =
        TNode(5, TNode::Minus, statement_number,
              {std::make_shared<TNode>(one), std::make_shared<TNode>(times)});
    TNode x = TNode(4, TNode::Variable, 1, "x");
    TNode assign =
        TNode(6, TNode::Assign, statement_number,
              {std::make_shared<TNode>(x), std::make_shared<TNode>(minus)});
    AssignEntity assign_entity = AssignEntity(assign, statement_number);

    REQUIRE(assign_entity.GetLeftHandSidePattern() == "x");
    REQUIRE(assign_entity.GetRightHandSidePattern() == "((1)-((y)*(z)))");
  }

  SECTION("x = 1 * y % z") {
    int statement_number = 1;
    TNode one = TNode(1, TNode::Constant, statement_number, 1);
    TNode y = TNode(2, TNode::Variable, statement_number, "y");
    TNode z = TNode(3, TNode::Variable, statement_number, "z");
    TNode modulo =
        TNode(4, TNode::Modulo, statement_number,
              {std::make_shared<TNode>(y), std::make_shared<TNode>(z)});
    TNode times =
        TNode(5, TNode::Multiply, statement_number,
              {std::make_shared<TNode>(one), std::make_shared<TNode>(modulo)});
    TNode x = TNode(4, TNode::Variable, 1, "x");
    TNode assign =
        TNode(6, TNode::Assign, statement_number,
              {std::make_shared<TNode>(x), std::make_shared<TNode>(times)});
    AssignEntity assign_entity = AssignEntity(assign, statement_number);

    REQUIRE(assign_entity.GetLeftHandSidePattern() == "x");
    REQUIRE(assign_entity.GetRightHandSidePattern() == "((1)*((y)%(z)))");
  }
}