#include "evaluator.h"

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(QueryablePkb& pkb,
                                                   QNode* q_tree) const {
  if (q_tree == nullptr) {
    return {};
  }

  // Postorder traversal
  std::unordered_set<std::string> left_result =
      Execute(pkb, q_tree->GetLeftNode());
  std::unordered_set<std::string> right_result =
      Execute(pkb, q_tree->GetRightNode());
  std::unordered_set<std::string> curr_result = q_tree->Fetch(pkb);

  curr_result.merge(left_result);
  curr_result.merge(right_result);

  return curr_result;
}
