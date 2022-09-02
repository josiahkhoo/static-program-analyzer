#include "q_node.h"

QNode::QNode(QNode* left_node, QNode* right_node) {
  left_node_ = left_node;
  right_node_ = right_node;
}

bool QNode::IsLeaf() const {
  if (left_node_ == nullptr && right_node_ == nullptr) {
    return true;
  } else {
    return false;
  }
}
