#include "evaluator.h"

#include <algorithm>
#include <map>

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

std::map<std::string, std::unordered_set<std::string>> map_union(
    const std::map<std::string, std::unordered_set<std::string>>& set_1,
    const std::map<std::string, std::unordered_set<std::string>>& set_2) {
  std::map<std::string, std::unordered_set<std::string>> res;
  for (const auto& p : set_1) {
    if (set_2.find(p.first) != set_2.end()) {
      res.insert({p.first, set_union(p.second, set_2.find(p.first)->second)});
    } else {
      res.insert(p);
    }
  }
  // Fill res-map with remaining set_2
  for (const auto& p : set_2) {
    if (res.find(p.first) == res.end()) {
      res.insert(p);
    }
  }
  return res;
}

std::map<std::string, std::unordered_set<std::string>> map_intersection(
    const std::map<std::string, std::unordered_set<std::string>>& set_1,
    const std::map<std::string, std::unordered_set<std::string>>& set_2) {
  std::map<std::string, std::unordered_set<std::string>> res;
  for (const auto& p : set_1) {
    if (set_2.find(p.first) != set_2.end()) {
      res.insert(
          {p.first, set_intersection(p.second, set_2.find(p.first)->second)});
    }
  }
  return res;
}

Evaluator::Evaluator() = default;

std::map<std::string, std::unordered_set<std::string>> Evaluator::ExecuteHelper(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree) const {
  std::map<std::string, std::unordered_set<std::string>> map_of_results;

  if (q_tree == nullptr) {
    return map_of_results;
  } else if (q_tree->IsLeaf()) {
    return q_tree->Fetch(pkb);
  }

  // Postorder traversal
  std::map<std::string, std::unordered_set<std::string>> left_result =
      ExecuteHelper(pkb, q_tree->GetLeftNode());
  std::map<std::string, std::unordered_set<std::string>> right_result =
      ExecuteHelper(pkb, q_tree->GetRightNode());
  std::map<std::string, std::unordered_set<std::string>> curr_result =
      q_tree->Fetch(pkb);

  std::map<std::string, std::unordered_set<std::string>> result;
  result = map_union(right_result, left_result);
  result = map_intersection(result, curr_result);
  return result;
}

std::unordered_set<std::string> Evaluator::Execute(
    const QueryablePkb& pkb, const std::shared_ptr<QNode>& q_tree,
    const Select& slt) const {
  std::map<std::string, std::unordered_set<std::string>> res =
      ExecuteHelper(pkb, q_tree);
  return res.find(slt.GetSynonym().GetIdentifier())->second;
}
