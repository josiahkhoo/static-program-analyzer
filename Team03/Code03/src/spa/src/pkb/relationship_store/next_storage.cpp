#include "next_storage.h"

/// Add Next Relationship
/// \param abstraction
void NextStorage::AddRelationship(NextAbstraction abstraction) {
  int previous = abstraction.GetLeftHandSide().GetStatementNumber();
  int next = abstraction.GetRightHandSide().GetStatementNumber();

  if (!previous_to_next_map_.emplace(previous, std::unordered_set<int>{next})
           .second) {
    previous_to_next_map_.at(previous).emplace(next);
  }
  if (!next_to_previous_map_.emplace(next, std::unordered_set<int>{previous})
           .second) {
    next_to_previous_map_.at(next).emplace(previous);
  }
}

/// GetPreviousStatements
/// \return Gets all statements executed immediately before another statement
std::unordered_set<std::string> NextStorage::GetPreviousStatements() const {
  std::unordered_set<std::string> res;
  if (!previous_to_next_map_.empty()) {
    for (auto i : previous_to_next_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetNextStatements
/// \return Gets all statements executed immediately after another statement
std::unordered_set<std::string> NextStorage::GetNextStatements() const {
  std::unordered_set<std::string> res;
  if (!next_to_previous_map_.empty()) {
    for (auto i : next_to_previous_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetPreviousStatements
/// \param statement_number
/// \return Gets all statements that were executed immediately before a
/// specified statement
std::unordered_set<std::string> NextStorage::GetPreviousStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (next_to_previous_map_.find(statement_number) !=
      next_to_previous_map_.end()) {
    for (auto entry : next_to_previous_map_.at(statement_number)) {
      res.emplace(std::to_string(entry));
    }
  }
  return res;
}

/// GetNextStatements
/// \param statement_number
/// \return Gets all statements that can be executed immediately after a
/// specified statement
std::unordered_set<std::string> NextStorage::GetNextStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (previous_to_next_map_.find(statement_number) !=
      previous_to_next_map_.end()) {
    for (auto entry : previous_to_next_map_.at(statement_number)) {
      res.emplace(std::to_string(entry));
    }
  }
  return res;
}

/// Clear Storage
void NextStorage::Clear() {
  previous_to_next_map_.clear();
  next_to_previous_map_.clear();
}
