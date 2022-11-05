#include "evaluator.h"

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(
    QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
    const std::shared_ptr<Select>& slt) const {
  if (slt == nullptr) {
    return {};
  }
  QResult res = q_tree->Fetch(pkb);
  return slt->GetResultSet(res, pkb);
}
