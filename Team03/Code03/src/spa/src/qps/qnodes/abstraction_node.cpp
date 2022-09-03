#include "abstraction_node.h"

AbstractionNode::AbstractionNode(SuchThat* clause,
                                 std::shared_ptr<QNode> left_node,
                                 std::shared_ptr<QNode> right_node)
    : clause_(clause), QNode(std::move(left_node), std::move(right_node)) {}

std::vector<Entity> AbstractionNode::Execute(QueryablePkb& pkb) {
  return pkb.query(*clause_);
}
