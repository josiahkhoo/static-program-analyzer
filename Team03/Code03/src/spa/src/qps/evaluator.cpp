#include "evaluator.h"

#include <algorithm>

std::unordered_set<std::string> set_intersection(
    const std::unordered_set<std::string>& set_1,
    const std::unordered_set<std::string>& set_2) {
  if (set_1.empty() || set_2.empty()) {
    return {};
  }
  if (set_2.size() < set_1.size()) {
    return set_intersection(set_2, set_1);
  }
  std::unordered_set<std::string> intersect_set;
  auto set2_itr = set_2.end();
  for (auto& set1_val : set_1) {
    if (set_2.find(set1_val) != set2_itr) {
      intersect_set.insert(set1_val);
    }
  }
  return intersect_set;
}

std::unordered_set<std::string> set_union(
    std::unordered_set<std::string> set_1,
    std::unordered_set<std::string> set_2) {
  if (set_1.empty()) {
    return set_2;
  } else if (set_2.empty()) {
    return set_1;
  }
  std::unordered_set<std::string> union_set;
  union_set.insert(set_1.begin(), set_1.end());
  union_set.insert(set_2.begin(), set_2.end());
  return union_set;
}

Evaluator::Evaluator() = default;

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree) const {
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