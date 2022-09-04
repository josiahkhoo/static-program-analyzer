#include "q_node.h"

QNode::QNode() : left_node_(nullptr), right_node_(nullptr){};

void QNode::SetLeftNode(QNode* leftNode) { left_node_ = leftNode; }

void QNode::SetRightNode(QNode* rightNode) { right_node_ = rightNode; }

QNode* QNode::GetLeftNode() const { return left_node_; }

QNode* QNode::GetRightNode() const { return right_node_; }

bool QNode::IsLeaf() const {
  return (left_node_ == nullptr && right_node_ == nullptr);
}

std::unordered_set<std::string> QNode::Fetch(QueryablePkb& pkb) { return {}; }
