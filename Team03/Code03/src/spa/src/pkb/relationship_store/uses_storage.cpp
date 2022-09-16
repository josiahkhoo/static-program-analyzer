#include "uses_storage.h"

void UsesStorage::AddRelationship(UsesPAbstraction abstraction) {
  std::string lhs = abstraction.GetLeftHandSide().GetName();
  std::string rhs = abstraction.GetRightHandSide().GetName();

  if (uses_p_map_.find(lhs) == uses_p_map_.end()) {
    uses_p_map_.emplace(lhs, std::make_unique<UsesPRelationship>(lhs));
  }
  uses_p_map_.find(lhs)->second->AddVariable(rhs);

  if (uses_p_by_map_.find(rhs) == uses_p_by_map_.end()) {
    uses_p_by_map_.emplace(rhs, std::make_unique<UsesPByRelationship>(rhs));
  }
  uses_p_by_map_.find(rhs)->second->AddProcedure(lhs);
}

void UsesStorage::AddRelationship(UsesSAbstraction abstraction) {
  int lhs = abstraction.GetLeftHandSide().GetStatementNumber();
  std::string rhs = abstraction.GetRightHandSide().GetName();

  if (uses_s_map_.find(lhs) == uses_s_map_.end()) {
    uses_s_map_.emplace(lhs, std::make_unique<UsesSRelationship>(lhs));
  }
  uses_s_map_.find(lhs)->second->AddVariable(rhs);

  if (uses_s_by_map_.find(rhs) == uses_s_by_map_.end()) {
    uses_s_by_map_.emplace(rhs, std::make_unique<UsesSByRelationship>(rhs));
  }
  uses_s_by_map_.find(rhs)->second->AddStatement(lhs);
}

// Gets all procedures that use variables
std::unordered_set<std::string> UsesStorage::GetUsesP() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_p_map_) {
    res.emplace(entry.first);
  }
  return res;
}

// Gets all variables used by a specified procedure
std::unordered_set<std::string> UsesStorage::GetUsesP(
    std::string procedure_name) const {
  if (uses_p_map_.find(procedure_name) == uses_p_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_p_map_.find(procedure_name)->second->GetVariables();
  return res;
}

// Gets all variables that are used by procedures
std::unordered_set<std::string> UsesStorage::GetUsesPBy() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_p_by_map_) {
    res.emplace(entry.first);
  }
  return res;
}

// Gets all procedures that use a specified variable
std::unordered_set<std::string> UsesStorage::GetUsesPBy(
    std::string variable_name) const {
  if (uses_p_by_map_.find(variable_name) == uses_p_by_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_p_by_map_.find(variable_name)->second->GetUses();
  return res;
}

// Gets all statements that use variables
std::unordered_set<std::string> UsesStorage::GetUsesS() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_s_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

// Gets all variables used by a specified statements
std::unordered_set<std::string> UsesStorage::GetUsesS(
    int statement_number) const {
  if (uses_s_map_.find(statement_number) == uses_s_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_s_map_.find(statement_number)->second->GetVariables();
  return res;
}

// Gets all variables that are used by statements
std::unordered_set<std::string> UsesStorage::GetUsesSBy() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_s_by_map_) {
    res.emplace(entry.first);
  }
  return res;
}

// Gets all statements that use a specified variable
std::unordered_set<std::string> UsesStorage::GetUsesSBy(
    std::string variable_name) const {
  if (uses_s_by_map_.find(variable_name) == uses_s_by_map_.end()) {
    return {};
  }
  std::unordered_set<int> res =
      uses_s_by_map_.find(variable_name)->second->GetUses();
  std::unordered_set<std::string> s;
  for (int i : res) {
    s.emplace(std::to_string(i));
  }
  return s;
}
