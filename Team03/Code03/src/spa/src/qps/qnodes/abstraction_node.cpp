#include "abstraction_node.h"

#include "common/clause/clause.h"

AbstractionNode::AbstractionNode(Clause clause) : QNode(), clause_(clause) {}

std::unordered_set<std::string> AbstractionNode::Fetch(QueryablePkb& pkb) {
  return pkb.QueryAllFollow(EntityType::CONSTANT);
}
