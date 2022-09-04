#include "abstraction_node.h"

AbstractionNode::AbstractionNode(Clause clause) : QNode(), clause_(clause) {}

std::vector<std::string> AbstractionNode::Fetch(QueryablePkb& pkb) {
  return pkb.query(clause_);
}
