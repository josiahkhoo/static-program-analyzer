#include "catch.hpp"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/while_entity.h"
#include "pkb/relationship_store/parent_storage.h"

TEST_CASE("Parent Storage Management", "[ParentStorage]") {
  TNode mock_while_node =
      TNode(1, TNode::While, 1, std::vector<std::shared_ptr<TNode>>());
  WhileEntity mock_lhs_one = WhileEntity(mock_while_node, 1);
  TNode mock_call_node =
      TNode(2, TNode::Call, 2, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_rhs_one = CallEntity(mock_call_node, 2);
  TNode mock_if_node =
      TNode(3, TNode::IfElseThen, 3, std::vector<std::shared_ptr<TNode>>());
  IfEntity mock_lhs_two = IfEntity(mock_if_node, 3);
  TNode mock_assign_node =
      TNode(4, TNode::Assign, 4, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_rhs_two = AssignEntity(mock_assign_node, 4);
  ParentAbstraction mock_parent_abstraction_one =
      ParentAbstraction(mock_lhs_one, mock_rhs_one);
  ParentAbstraction mock_parent_abstraction_two =
      ParentAbstraction(mock_lhs_two, mock_rhs_two);
  ParentStorage parent_storage;
  parent_storage.AddRelationship(mock_parent_abstraction_one);
  parent_storage.AddRelationship(mock_parent_abstraction_two);
  std::unordered_set<std::string> parent_list =
      parent_storage.GetParentStatements(2);
  std::unordered_set<std::string> parent_by_list =
      parent_storage.GetParentByStatements(1);
  std::unordered_set<std::string> all_parent_list =
      parent_storage.GetParentStatements();
  std::unordered_set<std::string> all_parent_by_list =
      parent_storage.GetParentByStatements();

  REQUIRE(*parent_list.find("1") == "1");
  REQUIRE(*parent_by_list.find("2") == "2");
  REQUIRE(all_parent_list.size() > 1);
  REQUIRE(all_parent_list.size() == all_parent_by_list.size());
}

/* ======================================
 * This tests storage of the case where an if statement that contains
 * 2 statements is nested in another if statement that also contains 2
 * statements.
 * ====================================== */
TEST_CASE("ParentT Storage Management", "[ParentStorage]") {
  TNode mock_while_node =
      TNode(1, TNode::While, 1, std::vector<std::shared_ptr<TNode>>());
  WhileEntity mock_lhs_one = WhileEntity(mock_while_node, 1);
  TNode mock_call_node_one =
      TNode(2, TNode::Call, 2, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_rhs_one = CallEntity(mock_call_node_one, 2);
  TNode mock_call_node_two =
      TNode(3, TNode::Call, 3, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_rhs_two = CallEntity(mock_call_node_two, 3);
  TNode mock_if_node =
      TNode(4, TNode::IfElseThen, 4, std::vector<std::shared_ptr<TNode>>());
  IfEntity mock_lhs_two = IfEntity(mock_if_node, 4);
  TNode mock_assign_node_one =
      TNode(5, TNode::Assign, 5, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_rhs_three = AssignEntity(mock_assign_node_one, 5);
  TNode mock_assign_node_two =
      TNode(6, TNode::Assign, 6, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_rhs_four = AssignEntity(mock_assign_node_two, 6);
  ParentTAbstraction mock_parent_abstraction_one =
      ParentTAbstraction(mock_lhs_one, mock_rhs_one);
  ParentTAbstraction mock_parent_abstraction_two =
      ParentTAbstraction(mock_lhs_one, mock_rhs_two);
  ParentTAbstraction mock_parent_abstraction_three =
      ParentTAbstraction(mock_lhs_one, mock_rhs_three);
  ParentTAbstraction mock_parent_abstraction_four =
      ParentTAbstraction(mock_lhs_one, mock_rhs_four);

  // Outer if statement is also parent of inner if statement
  ParentTAbstraction mock_parent_abstraction_five =
      ParentTAbstraction(mock_lhs_one, mock_lhs_two);
  ParentTAbstraction mock_parent_abstraction_six =
      ParentTAbstraction(mock_lhs_two, mock_rhs_three);
  ParentTAbstraction mock_parent_abstraction_seven =
      ParentTAbstraction(mock_lhs_two, mock_rhs_four);
  ParentStorage parent_storage;
  parent_storage.AddRelationship(mock_parent_abstraction_one);
  parent_storage.AddRelationship(mock_parent_abstraction_two);
  parent_storage.AddRelationship(mock_parent_abstraction_three);
  parent_storage.AddRelationship(mock_parent_abstraction_four);
  parent_storage.AddRelationship(mock_parent_abstraction_five);
  parent_storage.AddRelationship(mock_parent_abstraction_six);
  parent_storage.AddRelationship(mock_parent_abstraction_seven);
  std::unordered_set<std::string> inner_if_parent_t_list =
      parent_storage.GetParentTStatements(4);
  std::unordered_set<std::string> outer_if_parent_t_by_list =
      parent_storage.GetParentTByStatements(1);
  std::unordered_set<std::string> inner_statement_parent_t_list =
      parent_storage.GetParentTStatements(5);

  REQUIRE(*inner_if_parent_t_list.find("1") == "1");
  REQUIRE(outer_if_parent_t_by_list.size() == 5);
  REQUIRE(*inner_statement_parent_t_list.find("1") == "1");
  REQUIRE(*inner_statement_parent_t_list.find("4") == "4");
}
