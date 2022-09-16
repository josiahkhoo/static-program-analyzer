#include "abstraction_node.h"

#include <utility>

AbstractionNode::AbstractionNode(std::shared_ptr<QueryOperation> q_operation)
    : QNode(), q_operation_(std::move(q_operation)) {}

QResult AbstractionNode::Fetch(const QueryablePkb& pkb) {
  auto result = q_operation_->Fetch(pkb);
  std::vector<std::vector<std::string>> rows;
  // Reserve size to prevent vector from expanding each time
  rows.reserve(result.size());
  for (const auto& item : result) {
    rows.push_back({item});
  }
  return {rows, {q_operation_->GetSynonym()}};
}
