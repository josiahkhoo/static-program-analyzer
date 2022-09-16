#include "q_node.h"

#include <utility>

QNode::QNode(std::string syn)
    : syn_(std::move(syn)), left_node_(nullptr), right_node_(nullptr){};

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

std::map<std::string , std::unordered_set<std::string>> QNode::Fetch(const QueryablePkb &pkb) {
  return {};
}
