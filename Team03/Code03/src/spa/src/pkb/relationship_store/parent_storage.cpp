#include "parent_storage.h"

#include "parent_by_relationship.h"
#include "parent_relationship.h"

/// Add Parent Relationship
/// \param abstraction
void ParentStorage::AddRelationship(ParentAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  if (parent_map_.find(lhs) == parent_map_.end()) {
    parent_map_.emplace(lhs, std::make_unique<ParentRelationship>(lhs));
  }
  parent_map_.find(lhs)->second->AddParentByStatementNumber(rhs);

  if (parent_by_map_.find(rhs) == parent_by_map_.end()) {
    parent_by_map_.emplace(rhs, std::make_unique<ParentByRelationship>(rhs));
  }
  parent_by_map_.find(rhs)->second->AddParentStatementNumber(lhs);
}

/// Add ParentT Relationship
/// \param abstraction
void ParentStorage::AddRelationship(ParentTAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  if (parent_t_map_.find(lhs) == parent_t_map_.end()) {
    parent_t_map_.emplace(lhs, std::make_unique<ParentRelationship>(lhs));
  }
  parent_t_map_.find(lhs)->second->AddParentByStatementNumber(rhs);

  if (parent_t_by_map_.find(rhs) == parent_t_by_map_.end()) {
    parent_t_by_map_.emplace(rhs, std::make_unique<ParentByRelationship>(rhs));
  }
  parent_t_by_map_.find(rhs)->second->AddParentStatementNumber(lhs);
}

/// GetParentByStatements
/// \param statement_number
/// \return Gets all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> ParentStorage::GetParentByStatements(
    int statement_number) const {
  if (parent_map_.find(statement_number) == parent_map_.end()) {
    return {};
  }
  std::unordered_set<int> res =
      parent_map_.find(statement_number)->second->GetParentByStatementNumbers();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

/// GetParentTByStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> ParentStorage::GetParentTByStatements(
    int statement_number) const {
  if (parent_t_map_.find(statement_number) == parent_t_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = parent_t_map_.find(statement_number)
                                    ->second->GetParentByStatementNumbers();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

/// GetParentStatements
/// \param statement_number
/// \return Gets all statements that are direct parents of a specified statement
std::unordered_set<std::string> ParentStorage::GetParentStatements(
    int statement_number) const {
  if (parent_by_map_.find(statement_number) == parent_by_map_.end()) {
    return {};
  }
  std::unordered_set<int> res =
      parent_by_map_.find(statement_number)->second->GetParentStatementNumber();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
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
  if (parent_t_by_map_.find(statement_number) == parent_t_by_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = parent_t_by_map_.find(statement_number)
                                    ->second->GetParentStatementNumber();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
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
  //  parent_map_.clear();
  //  parent_by_map_.clear();
  //
  //  for (auto const& iter : parent_t_map_) {
  //    auto& parent_t = iter.second;
  //    parent_t.reset();
  //  }
}
