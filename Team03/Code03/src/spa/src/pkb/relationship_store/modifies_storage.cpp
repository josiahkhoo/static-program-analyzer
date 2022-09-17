#include "modifies_storage.h"

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

void ModifiesStorage::Clear() {
  stmt_to_var_modifies_map_.clear();
  proc_to_var_modifies_map_.clear();
  var_to_stmt_modifies_map_.clear();
  var_to_proc_modifies_map_.clear();
}
