#include "modifies_storage.h"

/// Add Procedure Modifies Relationship
/// \param abstraction
void ModifiesStorage::AddRelationship(ModifiesPAbstraction abstraction) {
  std::string proc_name = abstraction.GetLeftHandSide().GetName();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!proc_to_var_modifies_map_
           .emplace(proc_name, std::unordered_set<std::string>{var_name})
           .second) {
    proc_to_var_modifies_map_.at(proc_name).emplace(var_name);
  }
  if (!var_to_proc_modifies_map_
           .emplace(var_name, std::unordered_set<std::string>{proc_name})
           .second) {
    var_to_proc_modifies_map_.at(var_name).emplace(proc_name);
  }
}

/// Add Statement Modifies Relationship
/// \param abstraction
void ModifiesStorage::AddRelationship(ModifiesSAbstraction abstraction) {
  int statement_number = abstraction.GetLeftHandSide().GetStatementNumber();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!stmt_to_var_modifies_map_
           .emplace(statement_number, std::unordered_set<std::string>{var_name})
           .second) {
    stmt_to_var_modifies_map_.at(statement_number).emplace(var_name);
  }
  if (!var_to_stmt_modifies_map_
           .emplace(var_name, std::unordered_set<int>{statement_number})
           .second) {
    var_to_stmt_modifies_map_.at(var_name).emplace(statement_number);
  }
}

/// GetModifyingProcedures
/// \return Gets all procedures that modify variables
std::unordered_set<std::string> ModifiesStorage::GetModifyingProcedures()
    const {
  std::unordered_set<std::string> res;
  if (!proc_to_var_modifies_map_.empty()) {
    for (auto i : proc_to_var_modifies_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetVariablesModifiedByProcedures
/// \return Gets all variables that are modified by procedures
std::unordered_set<std::string>
ModifiesStorage::GetVariablesModifiedByProcedures() const {
  std::unordered_set<std::string> res;
  if (!var_to_proc_modifies_map_.empty()) {
    for (auto i : var_to_proc_modifies_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetModifyingStatements
/// \return Gets all statements that modify variables
std::unordered_set<std::string> ModifiesStorage::GetModifyingStatements()
    const {
  std::unordered_set<std::string> res;
  if (!stmt_to_var_modifies_map_.empty()) {
    for (auto i : stmt_to_var_modifies_map_) {
      res.emplace(std::to_string(i.first));
    }
  }
  return res;
}

/// GetVariablesModifiedByStatements
/// \return Gets all variables that are modified by statements
std::unordered_set<std::string>
ModifiesStorage::GetVariablesModifiedByStatements() const {
  std::unordered_set<std::string> res;
  if (!var_to_stmt_modifies_map_.empty()) {
    for (auto i : var_to_stmt_modifies_map_) {
      res.emplace(i.first);
    }
  }
  return res;
}

/// GetVariablesModifiedByProcedure
/// \param procedure_name
/// \return Gets all variables modified by a specified procedure
std::unordered_set<std::string>
ModifiesStorage::GetVariablesModifiedByProcedure(
    std::string procedure_name) const {
  std::unordered_set<std::string> res;
  if (proc_to_var_modifies_map_.find(procedure_name) !=
      proc_to_var_modifies_map_.end()) {
    for (auto var : proc_to_var_modifies_map_.at(procedure_name)) {
      res.emplace(var);
    }
  }
  return res;
}

/// GetVariablesModifiedByStatement
/// \param statement_number
/// \return Gets all variables modified by a specified statement
std::unordered_set<std::string>
ModifiesStorage::GetVariablesModifiedByStatement(int statement_number) const {
  std::unordered_set<std::string> res;
  if (stmt_to_var_modifies_map_.find(statement_number) !=
      stmt_to_var_modifies_map_.end()) {
    for (auto var : stmt_to_var_modifies_map_.at(statement_number)) {
      res.emplace(var);
    }
  }
  return res;
}

/// GetProceduresModifyingVariable
/// \param variable_name
/// \return Gets all procedures that modify a specified variable
std::unordered_set<std::string> ModifiesStorage::GetProceduresModifyingVariable(
    std::string variable_name) const {
  std::unordered_set<std::string> res;
  if (var_to_proc_modifies_map_.find(variable_name) !=
      var_to_proc_modifies_map_.end()) {
    for (auto proc : var_to_proc_modifies_map_.at(variable_name)) {
      res.emplace(proc);
    }
  }
  return res;
}

/// GetStatementsModifyingVariable
/// \param variable_name
/// \return Gets all statements that modify a specified variable
std::unordered_set<std::string> ModifiesStorage::GetStatementsModifyingVariable(
    std::string variable_name) const {
  std::unordered_set<std::string> res;
  if (var_to_stmt_modifies_map_.find(variable_name) !=
      var_to_stmt_modifies_map_.end()) {
    for (auto stmt : var_to_stmt_modifies_map_.at(variable_name)) {
      res.emplace(std::to_string(stmt));
    }
  }
  return res;
}
