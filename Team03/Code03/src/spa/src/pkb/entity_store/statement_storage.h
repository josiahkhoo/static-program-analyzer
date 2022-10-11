#ifndef SPA_STATEMENT_STORAGE_H
#define SPA_STATEMENT_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/while_entity.h"

class StatementStorage {
 public:
  StatementStorage();

  void AddCallStatement(CallEntity callEntity);

  void AddReadStatement(ReadEntity readEntity);

  void AddPrintStatement(PrintEntity printEntity);

  void AddAssignStatement(AssignEntity assignEntity);

  void AddIfStatement(IfEntity ifEntity);

  void AddWhileStatement(WhileEntity whileEntity);

  std::unordered_set<std::string> GetStatements() const;

  std::unordered_set<std::string> GetCallStatements() const;

  std::unordered_set<std::string> GetCallStatements(std::string proc) const;

  std::string GetCallStatementProcedure(int statement_number) const;

  std::unordered_set<std::string> GetReadStatements() const;

  std::unordered_set<std::string> GetReadStatements(std::string var) const;

  std::string GetReadStatementVariable(int statement_number) const;

  std::unordered_set<std::string> GetPrintStatements() const;

  std::unordered_set<std::string> GetPrintStatements(std::string var) const;

  std::string GetPrintStatementVariable(int statement_number) const;

  std::unordered_set<std::string> GetAssignStatements() const;

  std::unordered_set<std::string> GetIfStatements() const;

  std::unordered_set<std::string> GetWhileStatements() const;

 private:
  std::unordered_set<int> statement_list_;

  std::unordered_set<int> assign_statement_list_;
  std::unordered_set<int> if_statement_list_;
  std::unordered_set<int> while_statement_list_;

  std::unordered_map<int, std::string> call_statement_num_to_proc_map_;
  std::unordered_map<int, std::string> read_statement_num_to_var_map_;
  std::unordered_map<int, std::string> print_statement_num_to_var_map_;
};

#endif  // SPA_STATEMENT_STORAGE_H
