#include "entity_node.h"

EntityNode::EntityNode(Select select) : QNode(), select_(select) {}

std::unordered_set<std::string> EntityNode::Fetch(QueryablePkb& pkb) {
  return pkb.QueryAll(EntityType::VARIABLE);
}
