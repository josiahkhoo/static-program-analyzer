#include "entity_node.h"

#include <utility>

#include "q_result.h"

EntityNode::EntityNode(Select select) : QNode(), select_(std::move(select)) {}

QResult EntityNode::Fetch(const QueryablePkb& pkb) {
  auto result = pkb.QueryAll(select_.GetSynonym().GetEntityType());
  std::vector<std::vector<std::string>> rows;
  // Reserve size to prevent vector from expanding each time
  rows.reserve(result.size());
  for (const auto& item : result) {
    rows.push_back({item});
  }
  return {rows, {select_.GetSynonym()}};
}
