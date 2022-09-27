#ifndef SPA_MODIFIES_STORAGE_H
#define SPA_MODIFIES_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"

class ModifiesStorage {
 public:
  void AddRelationship(ModifiesPAbstraction abstraction);

  void AddRelationship(ModifiesSAbstraction abstraction);

  std::unordered_set<std::string> GetModifyingProcedures() const;

  std::unordered_set<std::string> GetVariablesModifiedByProcedures() const;

  std::unordered_set<std::string> GetModifyingStatements() const;

  std::unordered_set<std::string> GetVariablesModifiedByStatements() const;

  std::unordered_set<std::string> GetVariablesModifiedByProcedure(
      std::string procedure_name) const;

  std::unordered_set<std::string> GetProceduresModifyingVariable(
      std::string variable_name) const;

  std::unordered_set<std::string> GetVariablesModifiedByStatement(
      int statement_number) const;

  std::unordered_set<std::string> GetStatementsModifyingVariable(
      std::string variable_name) const;

  void Clear();

 private:
  std::unordered_map<int, std::unordered_set<std::string>>
      stmt_to_var_modifies_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      proc_to_var_modifies_map_;
  std::unordered_map<std::string, std::unordered_set<int>>
      var_to_stmt_modifies_map_;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      var_to_proc_modifies_map_;
};

#endif  // SPA_MODIFIES_STORAGE_H
