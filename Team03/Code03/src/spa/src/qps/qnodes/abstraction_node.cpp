#include "abstraction_node.h"

#include <cassert>
#include <utility>

AbstractionNode::AbstractionNode(std::shared_ptr<QueryOperation> q_operation)
    : QNode(), q_operation_(std::move(q_operation)) {}

QResult AbstractionNode::Fetch(const QueryablePkb& pkb) {
  if (GetLeftNode() || GetRightNode()) {
    return FetchWithChildren(pkb);
  }
  // Straight fetch if no children
  auto result = q_operation_->Fetch(pkb);
  std::vector<std::vector<std::string>> rows;
  // Reserve size to prevent vector from expanding each time
  rows.reserve(result.size());
  for (const auto& item : result) {
    rows.push_back({item});
  }
  return {rows, {q_operation_->GetSynonym()}};
}

QResult AbstractionNode::FetchWithChildren(const QueryablePkb& pkb) {
  // This has to be a double syn query op
  assert(q_operation_->GetType() == QueryOperation::DOUBLE_SYNONYM);

  auto lhs_result = GetLeftNode()->Fetch(pkb);
  auto rhs_result = GetRightNode()->Fetch(pkb);

  auto [syn1, syn2] = q_operation_->GetSynonymPair();
  auto possible_lhs = lhs_result.GetRows({syn1});
  auto possible_rhs = rhs_result.GetRows({syn2});

  std::vector<std::vector<std::string>> iterate_vector, check_vector;

  QueryOperation::IterateSide side =
      q_operation_->GetIterateSide(possible_lhs, possible_rhs);
  // Iterate over smaller size set
  if (side == QueryOperation::IterateSide::LHS) {
    iterate_vector = possible_lhs;
    check_vector = possible_rhs;
  } else {
    iterate_vector = possible_rhs;
    check_vector = possible_lhs;
  }

  std::vector<std::vector<std::string>> valid_relations;
  for (auto iter_row : iterate_vector) {
    std::unordered_set<std::string> result_set;
    if (side == QueryOperation::IterateSide::LHS) {
      result_set = q_operation_->FetchPossibleRhs(iter_row[0], pkb);
    } else {
      result_set = q_operation_->FetchPossibleLhs(iter_row[0], pkb);
    }
    for (auto check_row : check_vector) {
      if (result_set.erase(check_row[0]) > 0) {
        if (side == QueryOperation::IterateSide::LHS) {
          valid_relations.push_back({iter_row[0], check_row[0]});
        } else {
          valid_relations.push_back({check_row[0], iter_row[0]});
        }
      }
    }
  }
  QResult result = {{valid_relations}, {syn1, syn2}};
  return lhs_result.Join(result).Join(rhs_result);
}
