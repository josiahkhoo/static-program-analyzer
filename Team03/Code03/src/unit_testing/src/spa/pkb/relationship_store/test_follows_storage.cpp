#include "catch.hpp"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "pkb/entity_store/constant_storage.h"
#include "pkb/relationship_store/follows_storage.h"

TEST_CASE("Follows Storage Management", "[FollowsStorage]") {
  TNode mock_call_node_one =
      TNode(1, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_lhs_one = CallEntity(mock_call_node_one, 1);
  TNode mock_assign_node_one =
      TNode(2, TNode::Assign, 2, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_rhs_one = AssignEntity(mock_call_node_one, 2);
  TNode mock_call_node_two =
      TNode(3, TNode::Call, 3, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_lhs_two = CallEntity(mock_call_node_two, 3);
  TNode mock_assign_node_two =
      TNode(4, TNode::Assign, 4, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_rhs_two = AssignEntity(mock_call_node_two, 4);
  FollowsAbstraction mock_follows_abstraction_one = FollowsAbstraction(mock_lhs_one, mock_rhs_one);
  FollowsAbstraction mock_follows_abstraction_two = FollowsAbstraction(mock_lhs_two, mock_rhs_two);
  FollowsStorage follows_storage;
  follows_storage.AddRelationship(mock_follows_abstraction_one);
  follows_storage.AddRelationship(mock_follows_abstraction_two);
  std::unordered_set<std::string> follows_list =
      follows_storage.GetFollowsStatements(1);
  std::unordered_set<std::string> follows_by_list =
      follows_storage.GetFollowsByStatements(2);
  std::unordered_set<std::string> all_follows_list =
      follows_storage.GetFollowsStatements();
  std::unordered_set<std::string> all_follows_by_list =
      follows_storage.GetFollowsByStatements();

  REQUIRE(follows_list.find("2") != follows_list.end());
  REQUIRE(follows_by_list.find("1") != follows_list.end());
  REQUIRE(all_follows_list.size() > 1);
  REQUIRE(all_follows_list.size() == all_follows_by_list.size());
}

TEST_CASE("FollowsT Storage Management", "[FollowsStorage]") {
  TNode mock_call_node_one =
      TNode(1, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_line_one = CallEntity(mock_call_node_one, 1);
  TNode mock_assign_node_one =
      TNode(2, TNode::Assign, 2, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_line_two = AssignEntity(mock_call_node_one, 2);
  TNode mock_call_node_two =
      TNode(3, TNode::Call, 3, std::vector<std::shared_ptr<TNode>>());
  CallEntity mock_line_three = CallEntity(mock_call_node_two, 3);
  TNode mock_assign_node_two =
      TNode(4, TNode::Assign, 4, std::vector<std::shared_ptr<TNode>>());
  AssignEntity mock_line_four = AssignEntity(mock_call_node_two, 4);
  FollowsTAbstraction mock_follows_t_abstraction_one = FollowsTAbstraction(mock_line_one, mock_line_two);
  FollowsTAbstraction mock_follows_t_abstraction_two = FollowsTAbstraction(mock_line_one, mock_line_three);
  FollowsTAbstraction mock_follows_t_abstraction_three = FollowsTAbstraction(mock_line_one, mock_line_four);
  FollowsTAbstraction mock_follows_t_abstraction_four = FollowsTAbstraction(mock_line_two, mock_line_three);
  FollowsTAbstraction mock_follows_t_abstraction_five = FollowsTAbstraction(mock_line_two, mock_line_four);
  FollowsTAbstraction mock_follows_t_abstraction_six = FollowsTAbstraction(mock_line_three, mock_line_four);
  FollowsStorage follows_storage;
  follows_storage.AddRelationship(mock_follows_t_abstraction_one);
  follows_storage.AddRelationship(mock_follows_t_abstraction_two);
  follows_storage.AddRelationship(mock_follows_t_abstraction_three);
  follows_storage.AddRelationship(mock_follows_t_abstraction_four);
  follows_storage.AddRelationship(mock_follows_t_abstraction_five);
  follows_storage.AddRelationship(mock_follows_t_abstraction_six);
  std::unordered_set<std::string> follows_t_list =
      follows_storage.GetFollowsTStatements(1);
  std::unordered_set<std::string> follows_t_by_list =
      follows_storage.GetFollowsTByStatements(4);
  REQUIRE(follows_t_list.count("2"));
  REQUIRE(follows_t_list.count("3"));
  REQUIRE(follows_t_list.count("4"));
  REQUIRE(follows_t_by_list.count("1"));
  REQUIRE(follows_t_by_list.count("2"));
  REQUIRE(follows_t_by_list.count("3"));
}

// To add tests for clear()