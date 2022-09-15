#include "abstraction_node.h"

#include <utility>

AbstractionNode::AbstractionNode(std::shared_ptr<QueryOperation> q_operation)
    : QNode(std::move(q_operation->GetSyn())),
      q_operation_(std::move(q_operation)) {}

std::unordered_set<std::string> AbstractionNode::Fetch(
    const QueryablePkb &pkb) {
  return q_operation_->Fetch(pkb);
}
