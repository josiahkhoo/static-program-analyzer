#ifndef SPA_USES_STORAGE_H
#define SPA_USES_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"

class UsesStorage {
 public:
  void AddRelationship(UsesPAbstraction abstraction);

  void AddRelationship(UsesSAbstraction abstraction);

  std::unordered_set<std::string> GetUsingProcedures() const;

  std::unordered_set<std::string> GetVariablesUsedByProcedures() const;

  std::unordered_set<std::string> GetUsingStatements() const;

  std::unordered_set<std::string> GetVariablesUsedByStatements() const;

  std::unordered_set<std::string> GetVariablesUsedByProcedure(
      std::string procedure_name) const;

  std::unordered_set<std::string> GetProceduresUsingVariable(
      std::string variable_name) const;

  std::unordered_set<std::string> GetVariablesUsedByStatement(
      int statement_number) const;

  std::unordered_set<std::string> GetStatementsUsingVariable(
      std::string variable_name) const;

 private:
  std::unordered_map<int, std::unordered_set<std::string>>
      stmt_to_var_uses_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      proc_to_var_uses_map_;
  std::unordered_map<std::string, std::unordered_set<int>>
      var_to_stmt_uses_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      var_to_proc_uses_map_;
};

#endif  // SPA_USES_STORAGE_H
