#include "follows_storage.h"

void FollowsStorage::AddRelationship(FollowsAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  follows_map_.emplace(lhs, rhs);
  follows_by_map_.emplace(rhs, lhs);
}

void FollowsStorage::AddRelationship(FollowsTAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  if (follows_t_map_.find(lhs) == follows_t_map_.end()) {
    follows_t_map_.emplace(lhs, std::make_unique<FollowsTRelationship>(lhs));
  }
  follows_t_map_.find(lhs)->second->AddFollowsTByStatementNumber(rhs);

  if (follows_t_by_map_.find(rhs) == follows_t_by_map_.end()) {
    follows_t_by_map_.emplace(rhs,
                              std::make_unique<FollowsTByRelationship>(rhs));
  }
  follows_t_by_map_.find(rhs)->second->AddFollowsTStatementNumber(lhs);
}

std::unordered_set<std::string> FollowsStorage::GetFollowsStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_map_.find(statement_number) == follows_map_.end()) {
    return res;
  }
  res.emplace(std::to_string(follows_map_.find(statement_number)->second));
  return res;
}

std::unordered_set<std::string> FollowsStorage::GetFollowsTStatements(
    int statement_number) const {
  if (follows_t_map_.find(statement_number) == follows_t_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = follows_t_map_.find(statement_number)
                                    ->second->GetFollowsTByStatementNumbers();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

std::unordered_set<std::string> FollowsStorage::GetFollowsByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_by_map_.find(statement_number) == follows_by_map_.end()) {
    return res;
  }
  res.emplace(std::to_string(follows_by_map_.find(statement_number)->second));
  return res;
}

std::unordered_set<std::string> FollowsStorage::GetFollowsByStatements() const {
  std::unordered_set<std::string> res;
  for (auto entry : follows_by_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

std::unordered_set<std::string> FollowsStorage::GetFollowsTByStatements(
    int statement_number) const {
  if (follows_t_by_map_.find(statement_number) == follows_t_by_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = follows_t_by_map_.find(statement_number)
                                    ->second->GetFollowsTStatementNumber();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

std::unordered_set<std::string> FollowsStorage::GetFollowsStatements() const {
  std::unordered_set<std::string> res;
  for (auto entry : follows_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}
