#include "evaluator.h"

Evaluator::Evaluator() = default;

std::vector<std::string> Evaluator::Execute(QueryablePkb& pkb,
                                            QNode* q_tree) const {
  if (q_tree == nullptr) {
    return {};
  }

  // Postorder traversal
  std::vector<std::string> left_result = Execute(pkb, q_tree->GetLeftNode());
  std::vector<std::string> right_result = Execute(pkb, q_tree->GetRightNode());
  std::vector<std::string> curr_result = q_tree->Fetch(pkb);

  std::vector<std::string> merged_result = left_result;
  merged_result.insert(merged_result.end(), right_result.begin(),
                       right_result.end());
  merged_result.insert(merged_result.end(), curr_result.begin(),
                       curr_result.end());

  return merged_result;
}
