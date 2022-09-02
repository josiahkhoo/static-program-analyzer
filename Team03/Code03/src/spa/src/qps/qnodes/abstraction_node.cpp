#include "abstraction_node.h"

AbstractionNode::AbstractionNode(QueryTail* q_tail, QNode* left_node,
                                 QNode* right_node) : QNode(left_node, right_node) {
  q_tail_ = q_tail;
}

std::vector<Entity> AbstractionNode::Execute(QueryablePkb& pkb) {
  if (this->IsLeaf()) {
    return q_tail_->Filter(pkb);
  } else {
  }
}
