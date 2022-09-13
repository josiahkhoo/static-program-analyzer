#include "parent_storage.h"

#include "parent_t_by_relationship.h"
#include "parent_t_relationship.h"

void ParentStorage::AddRelationship(ParentAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  parent_map_.emplace(lhs, rhs);
  parent_by_map_.emplace(rhs, lhs);
}

void ParentStorage::AddRelationship(ParentTAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  int rhs = abstraction.GetRightHandSide().GetStatementNumber();

  if (parent_t_map_.find(lhs) == parent_t_map_.end()) {
    parent_t_map_.emplace(lhs, std::make_unique<ParentTRelationship>(lhs));
  }
  parent_t_map_.find(lhs)->second->AddParentTByStatementNumber(rhs);

  if (parent_t_by_map_.find(rhs) == parent_t_by_map_.end()) {
    parent_t_by_map_.emplace(rhs, std::make_unique<ParentTByRelationship>(rhs));
  }
  parent_t_by_map_.find(rhs)->second->AddParentTStatementNumber(lhs);
}

std::unordered_set<std::string> ParentStorage::GetParentByStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_map_.find(statement_number) == parent_map_.end()) {
    return res;
  }
  res.emplace(std::to_string(parent_map_.find(statement_number)->second));
  return res;
}

std::unordered_set<std::string> ParentStorage::GetParentTByStatements(
    int statement_number) const {
  if (parent_t_map_.find(statement_number) == parent_t_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = parent_t_map_.find(statement_number)
                                    ->second->GetParentTByStatementNumbers();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

std::unordered_set<std::string> ParentStorage::GetParentStatements(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (parent_by_map_.find(statement_number) == parent_by_map_.end()) {
    return res;
  }
  res.emplace(std::to_string(parent_by_map_.find(statement_number)->second));
  return res;
}

std::unordered_set<std::string> ParentStorage::GetParentByStatements() const {
  std::unordered_set<std::string> res;
  for (auto entry : parent_by_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

std::unordered_set<std::string> ParentStorage::GetParentTStatements(
    int statement_number) const {
  if (parent_t_by_map_.find(statement_number) == parent_t_by_map_.end()) {
    return {};
  }
  std::unordered_set<int> res = parent_t_by_map_.find(statement_number)
                                    ->second->GetParentTStatementNumber();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}

std::unordered_set<std::string> ParentStorage::GetParentStatements() const {
  std::unordered_set<std::string> res;
  for (auto entry : parent_map_) {
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
