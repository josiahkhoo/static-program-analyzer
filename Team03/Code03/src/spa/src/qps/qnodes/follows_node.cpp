#include "follows_node.h"

FollowsNode::FollowsNode(FollowsClause* clause, QNode* left_node,
                                 QNode* right_node)
    : clause_(*clause), QNode(left_node, right_node) {}

std::vector<Entity> FollowsNode::Execute(QueryablePkb& pkb) {
  if (this->IsLeaf()) {
    return pkb.queryFollows(clause_.GetLeftHandSide(),
                            clause_.GetRightHandSide());
  }
  return {};
}
