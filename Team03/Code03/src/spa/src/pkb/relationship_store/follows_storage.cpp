#include "follows_storage.h"

/// Add Follows Relationship
/// \param abstraction
void FollowsStorage::AddRelationship(FollowsAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  follows_map_.emplace(lhs, rhs);
  follows_by_map_.emplace(rhs, lhs);
}

/// Add FollowsT Relationship
/// \param abstraction
void FollowsStorage::AddRelationship(FollowsTAbstraction abstraction) {
  int followed = abstraction.GetLeftHandSide().GetStatementNumber();
  int follower = abstraction.GetRightHandSide().GetStatementNumber();

  if (!follows_t_map_.emplace(followed, std::unordered_set<int>{follower})
           .second) {
    follows_t_map_.at(followed).emplace(follower);
  }
  if (!follows_t_by_map_.emplace(follower, std::unordered_set<int>{followed})
           .second) {
    follows_t_by_map_.at(follower).emplace(followed);
  }
}

/// GetFollowsStatements
/// \param statement_number
/// \return Gets all statements directly following a specified statement
std::unordered_set<std::string> FollowsStorage::GetFollowsStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_map_.find(statement_number) != follows_map_.end()) {
    res.emplace(std::to_string(follows_map_.find(statement_number)->second));
  }
  return res;
}

/// GetFollowsTStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> FollowsStorage::GetFollowsTStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_t_map_.find(statement_number) != follows_t_map_.end()) {
    for (auto i : follows_t_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetFollowsByStatements
/// \param statement_number
/// \return Gets all statements directly followed by a specified statement
std::unordered_set<std::string> FollowsStorage::GetFollowsByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_by_map_.find(statement_number) != follows_by_map_.end()) {
    res.emplace(std::to_string(follows_by_map_.find(statement_number)->second));
  }
  return res;
}

/// GetFollowsByStatements
/// \return Gets all statements followed by any statement
std::unordered_set<std::string> FollowsStorage::GetFollowsByStatements() const {
  std::unordered_set<std::string> res;
  for (auto entry : follows_by_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

/// GetFollowsTByStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> FollowsStorage::GetFollowsTByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (follows_t_by_map_.find(statement_number) != follows_t_by_map_.end()) {
    for (auto i : follows_t_by_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetFollowsStatements
/// \return Gets all statements following any statement
std::unordered_set<std::string> FollowsStorage::GetFollowsStatements() const {
  std::unordered_set<std::string> res;
  if (!follows_map_.empty()) {
    for (auto i : follows_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// Clear Storage
void FollowsStorage::Clear() {
  follows_map_.clear();
  follows_by_map_.clear();
  follows_t_map_.clear();
  follows_t_by_map_.clear();
}
