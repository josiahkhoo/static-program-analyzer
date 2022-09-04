#include "entity_node.h"

EntityNode::EntityNode(Select select) : QNode(), select_(select) {}

std::vector<std::string> EntityNode::Fetch(QueryablePkb& pkb) {
  return pkb.query(select_.GetEntity());
}
