#include "abstraction_node.h"

AbstractionNode::AbstractionNode(SuchThat* clause, QNode* left_node,
                                 QNode* right_node)
    : clause_(*clause), QNode(left_node, right_node) {}

std::vector<Entity> AbstractionNode::Execute(QueryablePkb& pkb) {
  if (this->IsLeaf()) {
    return pkb.query(clause_);
  }
  return {};
}
