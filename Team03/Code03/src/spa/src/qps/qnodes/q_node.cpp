#include "q_node.h"

#include "q_result.h"

QNode::QNode() : left_node_(nullptr), right_node_(nullptr) {}

void QNode::SetLeftNode(std::shared_ptr<QNode> left_node) {
  left_node_ = std::move(left_node);
}

void QNode::SetRightNode(std::shared_ptr<QNode> right_node) {
  right_node_ = std::move(right_node);
}

std::shared_ptr<QNode> QNode::GetLeftNode() const { return left_node_; }

std::shared_ptr<QNode> QNode::GetRightNode() const { return right_node_; }

bool QNode::IsLeaf() const {
  return (left_node_ == nullptr && right_node_ == nullptr);
}

QResult QNode::Fetch(const QueryablePkb &) { return QResult(false); }
