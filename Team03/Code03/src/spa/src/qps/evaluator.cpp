#include "evaluator.h"

#include <algorithm>
#include <map>

Evaluator::Evaluator() = default;

QResult Evaluator::ExecuteHelper(const QueryablePkb& pkb,
                                 const std::shared_ptr<QNode>& q_tree) const {
  if (q_tree == nullptr) {
    return {{}, {}};
  } else if (q_tree->IsLeaf()) {
    return q_tree->Fetch(pkb);
  }

  // Postorder traversal
  QResult left_result = ExecuteHelper(pkb, q_tree->GetLeftNode());
  QResult right_result = ExecuteHelper(pkb, q_tree->GetRightNode());
  QResult curr_result = q_tree->Fetch(pkb);

  return left_result.Join(right_result).Join(curr_result);
}

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
    const Select& slt) const {
  QResult res = ExecuteHelper(pkb, q_tree);
  std::vector<std::vector<std::string>> rows = res.GetRows({slt.GetSynonym()});
  // Return single item rows for now
  std::unordered_set<std::string> single_item_set;
  single_item_set.reserve(rows.size());
  for (auto row : rows) {
    single_item_set.emplace(row[0]);
  }
  return single_item_set;
}
