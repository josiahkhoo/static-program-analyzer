#include "uses_storage.h"

/// Add Procedure Uses Relationship
/// \param abstraction
void UsesStorage::AddRelationship(UsesPAbstraction abstraction) {
  std::string proc_name = abstraction.GetLeftHandSide().GetName();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!proc_to_var_uses_map_
           .emplace(proc_name, std::unordered_set<std::string>{var_name})
           .second) {
    proc_to_var_uses_map_.at(proc_name).emplace(var_name);
  }
  if (!var_to_proc_uses_map_
           .emplace(var_name, std::unordered_set<std::string>{proc_name})
           .second) {
    var_to_proc_uses_map_.at(var_name).emplace(proc_name);
  }
}

/// Add Statement Uses Relationship
/// \param abstraction
void UsesStorage::AddRelationship(UsesSAbstraction abstraction) {
  int statement_number = abstraction.GetLeftHandSide().GetStatementNumber();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!stmt_to_var_uses_map_
           .emplace(statement_number, std::unordered_set<std::string>{var_name})
           .second) {
    stmt_to_var_uses_map_.at(statement_number).emplace(var_name);
  }
  if (!var_to_stmt_uses_map_
           .emplace(var_name, std::unordered_set<int>{statement_number})
           .second) {
    var_to_stmt_uses_map_.at(var_name).emplace(statement_number);
  }
}

/// GetUsingProcedures
/// \return Gets all procedures that use variables
std::unordered_set<std::string> UsesStorage::GetUsingProcedures() const {
  std::unordered_set<std::string> res;
  if (!proc_to_var_uses_map_.empty()) {
    for (auto i : proc_to_var_uses_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetVariablesUsedByProcedure
/// \param procedure_name
/// \return Gets all variables used by a specified procedure
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByProcedure(
    std::string procedure_name) const {
  std::unordered_set<std::string> res;
  if (proc_to_var_uses_map_.find(procedure_name) !=
      proc_to_var_uses_map_.end()) {
    for (auto var : proc_to_var_uses_map_.at(procedure_name)) {
      res.emplace(var);
    }
  }
  return res;
}

/// GetVariablesUsedByProcedures
/// \return Gets all variables that are used by procedures
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByProcedures()
    const {
  std::unordered_set<std::string> res;
  if (!var_to_proc_uses_map_.empty()) {
    for (auto i : var_to_proc_uses_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetProceduresUsingVariable
/// \param variable_name
/// \return Gets all procedures that use a specified variable
std::unordered_set<std::string> UsesStorage::GetProceduresUsingVariable(
    std::string variable_name) const {
  std::unordered_set<std::string> res;
  if (var_to_proc_uses_map_.find(variable_name) !=
      var_to_proc_uses_map_.end()) {
    for (auto proc : var_to_proc_uses_map_.at(variable_name)) {
      res.emplace(proc);
    }
  }
  return res;
}

/// GetUsingStatements
/// \return Gets all statements that use variables
std::unordered_set<std::string> UsesStorage::GetUsingStatements() const {
  std::unordered_set<std::string> res;
  if (!stmt_to_var_uses_map_.empty()) {
    for (auto i : stmt_to_var_uses_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetVariablesUsedByStatement
/// \param statement_number
/// \return Gets all variables used by a specified statement
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByStatement(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (stmt_to_var_uses_map_.find(statement_number) !=
      stmt_to_var_uses_map_.end()) {
    for (auto var : stmt_to_var_uses_map_.at(statement_number)) {
      res.emplace(var);
    }
  }
  return res;
}

/// GetVariablesUsedByStatements
/// \return Gets all variables that are used by statements
std::unordered_set<std::string> UsesStorage::GetVariablesUsedByStatements()
    const {
  std::unordered_set<std::string> res;
  if (!var_to_stmt_uses_map_.empty()) {
    for (auto i : var_to_stmt_uses_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetStatementsUsingVariable
/// \param variable_name
/// \return Gets all statements that use a specified variable
std::unordered_set<std::string> UsesStorage::GetStatementsUsingVariable(
    std::string variable_name) const {
  std::unordered_set<std::string> res;
  if (var_to_stmt_uses_map_.find(variable_name) !=
      var_to_stmt_uses_map_.end()) {
    for (auto stmt : var_to_stmt_uses_map_.at(variable_name)) {
      res.emplace(std::to_string(stmt));
    }
  }
  return res;
}

/// Clear Storage
void UsesStorage::Clear() {
  stmt_to_var_uses_map_.clear();
  proc_to_var_uses_map_.clear();
  var_to_stmt_uses_map_.clear();
  var_to_proc_uses_map_.clear();
}
