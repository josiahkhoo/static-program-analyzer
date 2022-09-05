#include "q_node.h"

QNode::QNode() : left_node_(nullptr), right_node_(nullptr){};

void QNode::SetLeftNode(std::shared_ptr<QNode> left_node) {
  left_node_ = left_node;
}

void QNode::SetRightNode(std::shared_ptr<QNode> right_node) {
  right_node_ = right_node;
}

std::shared_ptr<QNode> QNode::GetLeftNode() const { return left_node_; }

std::shared_ptr<QNode> QNode::GetRightNode() const { return right_node_; }

bool QNode::IsLeaf() const {
  return (left_node_ == nullptr && right_node_ == nullptr);
}

std::unordered_set<std::string> QNode::Fetch(QueryablePkb& pkb) { return {}; }
