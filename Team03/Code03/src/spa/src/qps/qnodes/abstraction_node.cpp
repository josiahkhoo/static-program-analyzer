#include "abstraction_node.h"

#include <utility>

#include "common/clause/clause.h"

AbstractionNode::AbstractionNode(std::shared_ptr<QueryOperation> q_operation)
    : QNode(), q_operation_(std::move(q_operation)) {}

std::unordered_set<std::string> AbstractionNode::Fetch(
    const QueryablePkb &pkb) {
  return q_operation_->Fetch(pkb);
}
