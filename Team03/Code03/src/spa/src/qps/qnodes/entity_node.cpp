#include "entity_node.h"

#include <utility>

EntityNode::EntityNode(Select* select, std::shared_ptr<QNode> left_node,
                       std::shared_ptr<QNode> right_node)
    : QNode(std::move(left_node), std::move(right_node)), select_(select) {}

std::vector<Entity> EntityNode::Execute(QueryablePkb& pkb) {
  return pkb.query(select_->GetEntity());
}