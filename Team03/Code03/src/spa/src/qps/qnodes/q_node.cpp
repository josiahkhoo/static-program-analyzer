#include "q_node.h"

#include <utility>

QNode::QNode(std::shared_ptr<QNode> left_node,
             std::shared_ptr<QNode> right_node)
    : left_node_(std::move(left_node)), right_node_(std::move(right_node)) {}

bool QNode::IsLeaf() const {
  return (left_node_ == nullptr && right_node_ == nullptr);
}

std::vector<Entity> QNode::Execute(QueryablePkb& pkb) {
  if (IsLeaf()) {
    return {};
  } else {
    return left_node_->Execute(pkb);
  }
}
