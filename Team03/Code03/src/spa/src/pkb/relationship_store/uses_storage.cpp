#include "uses_storage.h"

/// Add Procedure Uses Relationship
/// \param abstraction
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

/// Add Statement Uses Relationship
/// \param abstraction
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

/// GetUsingProcedures
/// \return Gets all procedures that use variables
std::unordered_set<std::string> UsesStorage::GetUsingProcedures() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_p_map_) {
    res.emplace(entry.first);
  }
  return res;
}

/// GetVariablesUsedByProcedure
/// \param procedure_name
/// \return Gets all variables used by a specified procedure
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByProcedure(
    std::string procedure_name) const {
  if (uses_p_map_.find(procedure_name) == uses_p_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_p_map_.find(procedure_name)->second->GetVariables();
  return res;
}

/// GetVariablesUsedByProcedures
/// \return Gets all variables that are used by procedures
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByProcedures() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_p_by_map_) {
    res.emplace(entry.first);
  }
  return res;
}

/// GetProceduresUsingVariable
/// \param variable_name
/// \return Gets all procedures that use a specified variable
std::unordered_set<std::string> UsesStorage::GetProceduresUsingVariable(
    std::string variable_name) const {
  if (uses_p_by_map_.find(variable_name) == uses_p_by_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_p_by_map_.find(variable_name)->second->GetUses();
  return res;
}

/// GetUsingStatements
/// \return Gets all statements that use variables
std::unordered_set<std::string> UsesStorage::GetUsingStatements() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_s_map_) {
    res.emplace(std::to_string(entry.first));
  }
  return res;
}

/// GetVariablesUsedByStatement
/// \param statement_number
/// \return Gets all variables used by a specified statement
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByStatement(
    int statement_number) const {
  if (uses_s_map_.find(statement_number) == uses_s_map_.end()) {
    return {};
  }
  std::unordered_set<std::string> res =
      uses_s_map_.find(statement_number)->second->GetVariables();
  return res;
}

/// GetVariablesUsedByStatements
/// \return Gets all variables that are used by statements
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByStatements() const {
  std::unordered_set<std::string> res;
  for (auto const& entry : uses_s_by_map_) {
    res.emplace(entry.first);
  }
  return res;
}

/// GetStatementsUsingVariable
/// \param variable_name
/// \return Gets all statements that use a specified variable
std::unordered_set<std::string> UsesStorage::GetStatementsUsingVariable(
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
