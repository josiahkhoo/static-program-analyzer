#include "entity_node.h"

#include <utility>

EntityNode::EntityNode(Select select) : QNode(), select_(std::move(select)) {}

std::unordered_set<std::string> EntityNode::Fetch(const QueryablePkb &pkb) {
  return pkb.QueryAll(select_.GetSynonym().GetEntityType());
}
