#include "evaluator.h"

#include <algorithm>
#include <iterator>

std::unordered_set<std::string> set_intersection(
    const std::unordered_set<std::string>& set_1,
    const std::unordered_set<std::string>& set_2) {
  if (set_1.empty() || set_2.empty()) {
    return {};
  }
  std::unordered_set<std::string> intersect_set;
  std::set_intersection(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(),
                        std::inserter(intersect_set, intersect_set.end()));
  return intersect_set;
}

std::unordered_set<std::string> set_union(
    std::unordered_set<std::string> set_1,
    std::unordered_set<std::string> set_2) {
  std::unordered_set<std::string> merged_set;
  std::set_union(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(),
                 std::inserter(merged_set, merged_set.end()));
  return merged_set;
}

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, std::shared_ptr<QNode> q_tree) const {
  if (q_tree == nullptr) {
    return {};
  } else if (q_tree->IsLeaf()) {
    return q_tree->Fetch(pkb);
  }

  // Postorder traversal
  std::unordered_set<std::string> left_result =
      Execute(pkb, q_tree->GetLeftNode());
  std::unordered_set<std::string> right_result =
      Execute(pkb, q_tree->GetRightNode());
  std::unordered_set<std::string> curr_result = q_tree->Fetch(pkb);

  std::unordered_set<std::string> result;
  result = set_union(right_result, left_result);
  result = set_intersection(result, curr_result);
  return result;
}