#include "catch.hpp"
#include "pkb/entity_store/constant_storage.h"

TEST_CASE("Constant Storage Management", "[ConstantStorage]") {
  TNode mock_constant_node =
      TNode(1, TNode::Constant, 1, std::vector<std::shared_ptr<TNode>>());
  ConstantEntity constant_entity = ConstantEntity(mock_constant_node, 8);
  ConstantStorage constant_storage;
  constant_storage.Clear();
  constant_storage.AddConstant(constant_entity);
  std::unordered_set<std::string> constant_list =
      constant_storage.GetConstants();
  REQUIRE(constant_list.find("8") != constant_list.end());
}

TEST_CASE("Clearing Constant List", "[ConstantStorage]") {
  TNode mock_constant_node =
      TNode(1, TNode::Constant, 1, std::vector<std::shared_ptr<TNode>>());
  ConstantEntity constant_entity = ConstantEntity(mock_constant_node, 8);
  ConstantStorage constant_storage;
  constant_storage.AddConstant(constant_entity);
  constant_storage.Clear();
  std::unordered_set<std::string> constant_list =
      constant_storage.GetConstants();
  REQUIRE(constant_list.find("8") == constant_list.end());
}
