#include "evaluator.h"

#include <algorithm>

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
    const std::shared_ptr<Select>& slt) const {
  QResult res = q_tree->Fetch(pkb);
  return slt->GetResultSet(res, pkb);
}
