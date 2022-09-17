#include "evaluator.h"

#include <algorithm>
#include <map>

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
    const Select& slt) const {
  QResult res = q_tree->Fetch(pkb);
  std::vector<std::vector<std::string>> rows = res.GetRows({slt.GetSynonym()});
  // Return single item rows for now
  std::unordered_set<std::string> single_item_set;
  single_item_set.reserve(rows.size());
  for (auto row : rows) {
    single_item_set.emplace(row[0]);
  }
  return single_item_set;
}
