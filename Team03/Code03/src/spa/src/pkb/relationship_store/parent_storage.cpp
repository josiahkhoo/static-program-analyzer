#include "parent_storage.h"

#include "parent_by_relationship.h"
#include "parent_relationship.h"

/// Add Parent Relationship
/// \param abstraction
void ParentStorage::AddRelationship(ParentAbstraction abstraction) {
  int parent = abstraction.GetLeftHandSide().GetStatementNumber();
  int child = abstraction.GetRightHandSide().GetStatementNumber();

  if (!parent_map_.emplace(parent, std::unordered_set<int>{child})
           .second) {
    parent_map_.at(parent).emplace(child);
  }
  if (!parent_by_map_.emplace(child, std::unordered_set<int>{parent})
           .second) {
    parent_by_map_.at(child).emplace(parent);
  }
}

/// Add ParentT Relationship
/// \param abstraction
void ParentStorage::AddRelationship(ParentTAbstraction abstraction) {
  int parent = abstraction.GetLeftHandSide().GetStatementNumber();
  int child = abstraction.GetRightHandSide().GetStatementNumber();

  if (!parent_t_map_.emplace(parent, std::unordered_set<int>{child})
           .second) {
    parent_t_map_.at(parent).emplace(child);
  }
  if (!parent_t_by_map_.emplace(child, std::unordered_set<int>{parent})
           .second) {
    parent_t_by_map_.at(child).emplace(parent);
  }
}

/// GetParentByStatements
/// \param statement_number
/// \return Gets all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> ParentStorage::GetParentByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_map_.find(statement_number) != parent_map_.end()) {
    for (auto i : parent_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetParentTByStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> ParentStorage::GetParentTByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_t_map_.find(statement_number) != parent_t_map_.end()) {
    for (auto i : parent_t_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetParentStatements
/// \param statement_number
/// \return Gets all statements that are direct parents of a specified statement
std::unordered_set<std::string> ParentStorage::GetParentStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_by_map_.find(statement_number) != parent_by_map_.end()) {
    for (auto i : parent_by_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetParentByStatements
/// \return Gets all statements that are direct children of any statement
std::unordered_set<std::string> ParentStorage::GetParentByStatements() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : parent_by_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

/// GetParentTStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> ParentStorage::GetParentTStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_t_by_map_.find(statement_number) != parent_t_by_map_.end()) {
    for (auto i : parent_t_by_map_.at(statement_number)) {
      res.emplace(std::to_string(i));
    }
  }
  return res;
}

/// GetParentStatements
/// \return Gets all statements that are direct parents of any statement
std::unordered_set<std::string> ParentStorage::GetParentStatements() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : parent_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

void ParentStorage::Clear() {
    parent_map_.clear();
    parent_by_map_.clear();
    parent_t_map_.clear();
    parent_t_by_map_.clear();
}
