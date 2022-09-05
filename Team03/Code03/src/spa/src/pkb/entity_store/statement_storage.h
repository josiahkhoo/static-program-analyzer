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

  std::unordered_set<std::string> GetStatements();

  std::unordered_set<std::string> GetCallStatements();

  std::unordered_set<std::string> GetReadStatements();

  std::unordered_set<std::string> GetPrintStatements();

  std::unordered_set<std::string> GetAssignStatements();

  std::unordered_set<std::string> GetIfStatements();

  std::unordered_set<std::string> GetWhileStatements();

  // Empty storage
  void Clear();

 private:
  static std::unordered_set<std::string> statementList;
  static std::unordered_set<std::string> callStatementList;
  static std::unordered_set<std::string> readStatementList;
  static std::unordered_set<std::string> printStatementList;
  static std::unordered_set<std::string> assignStatementList;
  static std::unordered_set<std::string> ifStatementList;
  static std::unordered_set<std::string> whileStatementList;
};

#endif  // SPA_STATEMENT_STORAGE_H
