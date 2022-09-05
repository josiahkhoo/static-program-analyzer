#include "catch.hpp"
#include "pkb/entity_store/variable_storage.h"

TEST_CASE("Variable Storage Management", "[VariableStorage]") {
  TNode mock_variable_node =
      TNode(1, TNode::Variable, 1, std::vector<std::shared_ptr<TNode>>());
  VariableEntity variable_entity = VariableEntity(mock_variable_node, "X");
  VariableStorage variable_storage;
  variable_storage.Clear();
  variable_storage.AddVariable(variable_entity);
  std::unordered_set<std::string> variable_list =
      variable_storage.GetVariables();
  REQUIRE(variable_list.find("X") != variable_list.end());
}

TEST_CASE("Clearing Variable List", "[VariableStorage]") {
  TNode mock_variable_node =
      TNode(1, TNode::Variable, 1, std::vector<std::shared_ptr<TNode>>());
  VariableEntity variable_entity = VariableEntity(mock_variable_node, "X");
  VariableStorage variable_storage;
  variable_storage.AddVariable(variable_entity);
  variable_storage.Clear();
  std::unordered_set<std::string> variable_list =
      variable_storage.GetVariables();
  REQUIRE(variable_list.find("X") == variable_list.end());
}
