#include "entity_node.h"

EntityNode::EntityNode(Select* select, QNode* left_node, QNode* right_node)
    : QNode(left_node, right_node) {
  select_ = select;
}

std::vector<Entity> EntityNode::Execute(QueryablePkb& pkb) {
  return {};
}
