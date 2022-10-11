#ifndef SPA_ENTITY_MANAGER_H
#define SPA_ENTITY_MANAGER_H

#include <string>
#include <vector>

#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "common/entity/while_entity.h"
#include "constant_storage.h"
#include "procedure_storage.h"
#include "statement_storage.h"
#include "variable_storage.h"

class EntityManager {
 public:
  EntityManager();
  /* ====================================
   * General Entity Adder Methods
   * ==================================== */
  // store procedure to ProcedureStorage
  void AddProcedure(ProcedureEntity procedure);

  // store variable to VariableStorage
  void AddVariable(VariableEntity variable);

  // store constant to ConstantStorage
  void AddConstant(ConstantEntity constant);

  // store call statement to StatementStorage
  void AddCallStatement(CallEntity statement);

  // store read statement to StatementStorage
  void AddReadStatement(ReadEntity statement);

  // store print statement to StatementStorage
  void AddPrintStatement(PrintEntity statement);

  // store assign statement to StatementStorage
  void AddAssignStatement(AssignEntity statement);

  // store if statement to StatementStorage
  void AddIfStatement(IfEntity statement);

  // store while statement to StatementStorage
  void AddWhileStatement(WhileEntity statement);

  /* ====================================
   * General Entity Getter Methods
   * ==================================== */
  // get stored procedures in ProcedureStorage
  std::unordered_set<std::string> GetProcedures() const;

  // get stored variables in VariableStorage
  std::unordered_set<std::string> GetVariables() const;

  // get stored constants in ConstantStorage
  std::unordered_set<std::string> GetConstants() const;

  // get stored statements in StatementStorage
  std::unordered_set<std::string> GetStatements() const;

  // get stored call statements in StatementStorage
  std::unordered_set<std::string> GetCallStatements() const;

  // get stored call statements calling proc in StatementStorage
  std::unordered_set<std::string> GetCallStatements(std::string proc) const;

  std::string GetCallStatementProcedure(int statement_number) const;

  // get stored read statements in StatementStorage
  std::unordered_set<std::string> GetReadStatements() const;

  // get stored read statements reading var in StatementStorage
  std::unordered_set<std::string> GetReadStatements(std::string var) const;

  std::string GetReadStatementVariable(int statement_number) const;

  // get stored print statements in StatementStorage
  std::unordered_set<std::string> GetPrintStatements() const;

  // get stored print statements printing var in StatementStorage
  std::unordered_set<std::string> GetPrintStatements(std::string var) const;

  std::string GetPrintStatementVariable(int statement_number) const;

  // get stored assign statements in StatementStorage
  std::unordered_set<std::string> GetAssignStatements() const;

  // get stored if statements in StatementStorage
  std::unordered_set<std::string> GetIfStatements() const;

  // get stored while statements in StatementStorage
  std::unordered_set<std::string> GetWhileStatements() const;

 private:
  ProcedureStorage procedure_store_;
  StatementStorage statement_store_;
  VariableStorage variable_store_;
  ConstantStorage constant_store_;
};

#endif  // SPA_ENTITY_MANAGER_H
