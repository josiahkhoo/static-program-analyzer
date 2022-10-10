#include "next_storage.h"

/// Add Next Relationship
/// \param abstraction
void NextStorage::AddRelationship(NextAbstraction abstraction) {
  int precedent = abstraction.GetLeftHandSide().GetStatementNumber();
  int next = abstraction.GetRightHandSide().GetStatementNumber();

  if (!precedent_to_next_map_.emplace(precedent, std::unordered_set<int>{next})
           .second) {
    precedent_to_next_map_.at(precedent).emplace(next);
  }
  if (!next_to_precedent_map_.emplace(next, std::unordered_set<int>{precedent})
           .second) {
    next_to_precedent_map_.at(next).emplace(precedent);
  }
}

/// GetNextByStatements
/// \return Gets all statements executed immediately before another statement
std::unordered_set<std::string> NextStorage::GetNextByStatements() const {
  std::unordered_set<std::string> res;
  if (!precedent_to_next_map_.empty()) {
    for (auto i : precedent_to_next_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetNextStatements
/// \return Gets all statements executed immediately after another statement
std::unordered_set<std::string> NextStorage::GetNextStatements() const {
  std::unordered_set<std::string> res;
  if (!next_to_precedent_map_.empty()) {
    for (auto i : next_to_precedent_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetNextByStatements
/// \param statement_number
/// \return Gets all statements that were executed immediately before a
/// specified statement
std::unordered_set<std::string> NextStorage::GetNextByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (next_to_precedent_map_.find(statement_number) !=
      next_to_precedent_map_.end()) {
    for (auto entry : next_to_precedent_map_.at(statement_number)) {
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
  if (precedent_to_next_map_.find(statement_number) !=
      precedent_to_next_map_.end()) {
    for (auto entry : precedent_to_next_map_.at(statement_number)) {
      res.emplace(std::to_string(entry));
    }
  }
  return res;
}

/// Clear Storage
void NextStorage::Clear() {
  precedent_to_next_map_.clear();
  next_to_precedent_map_.clear();
}
