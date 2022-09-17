#include "entity_node.h"

#include <utility>

#include "q_result.h"

EntityNode::EntityNode(Synonym synonym)
    : QNode(), synonym_(std::move(synonym)) {}

QResult EntityNode::Fetch(const QueryablePkb& pkb) {
  auto result = pkb.QueryAll(synonym_.GetEntityType());
  std::vector<std::vector<std::string>> rows;
  // Reserve size to prevent vector from expanding each time
  rows.reserve(result.size());
  for (const auto& item : result) {
    rows.push_back({item});
  }
  return {rows, {synonym_}};
}
