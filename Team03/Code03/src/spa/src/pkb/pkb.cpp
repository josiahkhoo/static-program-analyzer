#include "pkb.h"

#include <cassert>
#include <stdexcept>
#include <vector>

#include "common/reference/attribute_name.h"

PKB::PKB() {}

void PKB::Store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entity_manager_.AddProcedure(entity);
  }
}

void PKB::Store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entity_manager_.AddVariable(entity);
  }
}

void PKB::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}

void PKB::Store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entity_manager_.AddCallStatement(entity);
  }
}

void PKB::Store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entity_manager_.AddReadStatement(entity);
  }
}

void PKB::Store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entity_manager_.AddPrintStatement(entity);
  }
}

void PKB::Store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entity_manager_.AddAssignStatement(entity);
    pattern_manager_.AddAssignPattern(entity);
  }
}

void PKB::Store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entity_manager_.AddIfStatement(entity);
  }
}

void PKB::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}

void PKB::Store(std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ParentAbstraction> abstractions) {
  for (const ParentAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ParentTAbstraction> abstractions) {
  for (const ParentTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<CallsAbstraction> abstractions) {
  for (const CallsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<CallsTAbstraction> abstractions) {
  for (const CallsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<UsesSAbstraction> abstractions) {
  for (const UsesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<UsesPAbstraction> abstractions) {
  for (const UsesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ModifiesSAbstraction> abstractions) {
  for (const ModifiesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ModifiesPAbstraction> abstractions) {
  for (const ModifiesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<WhilePatternAbstraction> abstractions) {
  for (const WhilePatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddWhilePattern(abstraction);
  }
}

void PKB::Store(std::vector<IfPatternAbstraction> abstractions) {
  for (const IfPatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddIfPattern(abstraction);
  }
}

void PKB::Store(std::vector<CFG> cfgs) {
  for (const CFG& cfg : cfgs) {
    relationship_manager_.AddCFG(cfg);
  }
}

std::unordered_set<std::string> PKB::QueryAll(EntityType type) const {
  switch (type) {
    case PROCEDURE:
      return entity_manager_.GetProcedures();
    case CONSTANT:
      return entity_manager_.GetConstants();
    case VARIABLE:
      return entity_manager_.GetVariables();
    case STATEMENT:
      return entity_manager_.GetStatements();
    case CALL:
      return entity_manager_.GetCallStatements();
    case READ:
      return entity_manager_.GetReadStatements();
    case PRINT:
      return entity_manager_.GetPrintStatements();
    case ASSIGN:
      return entity_manager_.GetAssignStatements();
    case IF:
      return entity_manager_.GetIfStatements();
    case WHILE:
      return entity_manager_.GetWhileStatements();
  }
}

/// QueryAllFollows
/// \param type
/// \return Query all statements following any statement of a specified type
std::unordered_set<std::string> PKB::QueryAllFollows(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllFollowsBy
/// \param type
/// \return Query all statements followed by any statement of a specified type
std::unordered_set<std::string> PKB::QueryAllFollowsBy(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsByStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllFollows
/// \param type
/// \return Gets all statements following or followed by any statement
std::unordered_set<std::string> PKB::QueryAllFollowsRelations() const {
  return relationship_manager_.GetFollowsStatements();
}

/// QueryFollows
/// \param statement_number
/// \param type
/// \return Query all statements directly following a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollows(int statement_number,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryFollowsBy
/// \param statement_number
/// \param type
/// \return Query all statements directly followed by a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsBy(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryFollowsT
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsT(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsTStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  };
  return result;
}

/// QueryFollowsTBy
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsTBy(int statement_number,
                                                     EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsTByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllParent
/// \return Query all statements that are direct parents of any statement
std::unordered_set<std::string> PKB::QueryAllParent(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllParentBy
/// \return Query all statements that are direct children of any statement
std::unordered_set<std::string> PKB::QueryAllParentBy(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentByStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllParentsRelations
/// \return Query all parent and children statements of any statement
std::unordered_set<std::string> PKB::QueryAllParentsRelations() const {
  std::unordered_set<std::string> res =
      relationship_manager_.GetParentStatements();
  std::unordered_set<std::string> children =
      relationship_manager_.GetParentByStatements();
  res.merge(children);
  return res;
}

/// QueryParent
/// \param statement_number
/// \param type
/// \return Query all statements that are direct parents of a specified
/// statement
std::unordered_set<std::string> PKB::QueryParent(int statement_number,
                                                 EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryParentBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> PKB::QueryParentBy(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryParentT
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> PKB::QueryParentT(int statement_number,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentTStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  };
  return result;
}

/// QueryParentTBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> PKB::QueryParentTBy(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentTByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/* ====================================
 * Uses Query Methods
 * ==================================== */

/// QueryAllUses
/// \param type
/// \return All statements or procedures that uses some Variable
std::unordered_set<std::string> PKB::QueryAllUses(EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetUsingProcedures();
  }
  std::unordered_set<std::string> statements =
      relationship_manager_.GetUsingStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllUsesBy
/// \param type
/// \return All Variables that are used by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> PKB::QueryAllUsesBy(EntityType type) const {
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    return {};
  } else if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetVariablesUsedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    return relationship_manager_.GetVariablesUsedByStatements();
  } else {
    std::unordered_set<std::string> result;
    std::unordered_set<std::string> typed_statements = QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesUsedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
    return result;
  }
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified statement
std::unordered_set<std::string> PKB::QueryUsesS(int statement_number,
                                                EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetVariablesUsedByStatement(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryUsesSBy
/// \param identifier
/// \param type
/// \return Query all statements that use a specified variable
std::unordered_set<std::string> PKB::QueryUsesSBy(std::string identifier,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetStatementsUsingVariable(identifier);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified procedure
std::unordered_set<std::string> PKB::QueryUsesP(std::string identifier,
                                                EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetVariablesUsedByProcedure(identifier);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryUsesPBy
/// \param identifier
/// \param type
/// \return Query all procedures that use a specified variable
std::unordered_set<std::string> PKB::QueryUsesPBy(std::string identifier,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetProceduresUsingVariable(identifier);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/* ====================================
 * Modifies Query Methods
 * ==================================== */

/// QueryAllModifies
/// \param type
/// \return All statements or procedures that modifies some Variable
std::unordered_set<std::string> PKB::QueryAllModifies(EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetModifyingProcedures();
  }
  std::unordered_set<std::string> statements =
      relationship_manager_.GetModifyingStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllModifiesBy
/// \param type
/// \return All Variables that are modified by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> PKB::QueryAllModifiesBy(EntityType type) const {
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    return {};
  } else if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetVariablesModifiedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    return relationship_manager_.GetVariablesModifiedByStatements();
  } else {
    std::unordered_set<std::string> result;
    std::unordered_set<std::string> typed_statements = QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesModifiedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
    return result;
  }
}

/// QueryModifiesS
/// \param statement_number
/// \return Variables modified in given statement_number
std::unordered_set<std::string> PKB::QueryModifiesS(
    int statement_number) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetVariablesModifiedByStatement(statement_number);
  return result;
}

/// QueryModifiesSBy
/// \param identifier
/// \param type
/// \return Statements that modifies given Variable identifier
std::unordered_set<std::string> PKB::QueryModifiesSBy(std::string identifier,
                                                      EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetStatementsModifyingVariable(identifier);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryModifiesP
/// \param identifier
/// \return Variables modified in given Procedure identifier
std::unordered_set<std::string> PKB::QueryModifiesP(
    std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetVariablesModifiedByProcedure(identifier);
  return result;
}

/// QueryModifiesPBy
/// \param identifier
/// \return Procedures that modifies given Variable identifier
std::unordered_set<std::string> PKB::QueryModifiesPBy(
    std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetProceduresModifyingVariable(identifier);
  return result;
}

/* ====================================
 * Calls Query Methods
 * ==================================== */
/// QueryAllCalls
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> PKB::QueryAllCalls() const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsProcedures();
  return result;
}

/// QueryAllCallsBy
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> PKB::QueryAllCallsBy() const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsByProcedures();
  return result;
}

/// QueryAllCallsBy
/// \return Query all procedures that call or are called by any procedure
std::unordered_set<std::string> PKB::QueryAllCallsRelations() const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsProcedures();
  std::unordered_set<std::string> called =
      relationship_manager_.GetCallsByProcedures();
  result.merge(called);
  return result;
}

/// QueryCalls
/// \param identifier
/// \return Gets all procedures that directly call a specified procedure
std::unordered_set<std::string> PKB::QueryCalls(std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsProcedures(identifier);
  return result;
}

/// QueryCallsBy
/// \param identifier
/// \return Gets all procedures that are directly called by a specified
/// procedure
std::unordered_set<std::string> PKB::QueryCallsBy(
    std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsByProcedures(identifier);
  return result;
}

/// QueryCallsT
/// \param identifier
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
std::unordered_set<std::string> PKB::QueryCallsT(std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsTProcedures(identifier);
  return result;
}

/// QueryCallsTBy
/// \param identifier
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
std::unordered_set<std::string> PKB::QueryCallsTBy(
    std::string identifier) const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsTByProcedures(identifier);
  return result;
}

/* ====================================
 * Next Query Methods
 * ==================================== */
/// QueryAllNext
/// \return Query all statements that come next to some statement
std::unordered_set<std::string> PKB::QueryAllNext(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetAllNext();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllPrevious
/// \return Query all statements that come previous to some statement
std::unordered_set<std::string> PKB::QueryAllPrevious(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetAllPrevious();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryAllNext
/// \return Query all statements that come next or previous to some statement
std::unordered_set<std::string> PKB::QueryAllNextRelations() const {
  std::unordered_set<std::string> result = relationship_manager_.GetAllNext();
  std::unordered_set<std::string> previous =
      relationship_manager_.GetAllPrevious();
  result.merge(previous);
  return result;
}

/// QueryNext
/// \param statement_number statement
/// \return Query statement(s) that immediately comes next after given statement
std::unordered_set<std::string> PKB::QueryNext(int statement_number,
                                               EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetNext(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryPrevious
/// \param statement_number statement
/// \return Query statement(s) that immediately comes previous before given
/// statement
std::unordered_set<std::string> PKB::QueryPrevious(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetPrevious(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryNextT
/// \param statement_number statement
/// \return Query statement(s) that comes nextT after given statement
std::unordered_set<std::string> PKB::QueryNextT(int statement_number,
                                                EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetNextT(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/// QueryPreviousT
/// \param statement_number statement
/// \return Query statement(s) that comes previousT before given statement
std::unordered_set<std::string> PKB::QueryPreviousT(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetPreviousT(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

/* ====================================
 * Affects Query Methods
 * ==================================== */

/// QueryAllAffects
/// \return Query all assign statements that affects some other statement
std::unordered_set<std::string> PKB::QueryAllAffects() const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAllAffects(assigns, calls, reads);
}

/// QueryAllAffectsBy
/// \return Query all assign statements that are affected by some other
/// statement
std::unordered_set<std::string> PKB::QueryAllAffectsBy() const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAllAffectsBy(assigns, calls, reads);
}

/// QueryAffects
/// \param statement_number statement
/// \return Query all assign statements that affects given statement
std::unordered_set<std::string> PKB::QueryAffects(int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAffects(assigns, calls, reads,
                                          statement_number);
}

/// QueryAffectsBy
/// \param statement_number statement
/// \return Query all assign statements that are affected by given statement
std::unordered_set<std::string> PKB::QueryAffectsBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAffectsBy(assigns, calls, reads,
                                            statement_number);
}

/// QueryAffectsT
/// \param statement_number statement
/// \return Query all assign statements that affectsT given statement
std::unordered_set<std::string> PKB::QueryAffectsT(int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAffectsT(assigns, calls, reads,
                                           statement_number);
}

/// QueryAffectsTBy
/// \param statement_number statement
/// \return Query all assign statements that are affectedT by given statement
std::unordered_set<std::string> PKB::QueryAffectsTBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAffectsTBy(assigns, calls, reads,
                                             statement_number);
}

/* ====================================
 * Assign Pattern Query Methods
 * ==================================== */

std::unordered_set<std::string> PKB::QueryAllAssignPattern(
    Expression exp) const {
  return pattern_manager_.GetAllPattern(exp);
}

std::unordered_set<std::string> PKB::QueryAssignPattern(std::string lhs,
                                                        Expression exp) const {
  return pattern_manager_.GetPattern(lhs, exp);
}

std::unordered_set<std::string> PKB::QueryPatternVariablesFromAssign(
    int) const {
  return {};
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

/// QueryAllWhilePattern
/// \return Get all While Statements that use a variable in conditional
/// container
std::unordered_set<std::string> PKB::QueryAllWhilePattern() const {
  return pattern_manager_.GetAllWhilePattern();
}

/// QueryWhilePattern
/// \param ident
/// \return Get all While Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> PKB::QueryWhilePattern(
    std::string ident) const {
  return pattern_manager_.GetWhilePattern(ident);
}

/// QueryPatternVariablesFromWhile
/// \param statement_number
/// \return Get all variables used in conditional container of given While
/// Statement
std::unordered_set<std::string> PKB::QueryPatternVariablesFromWhile(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromWhile(statement_number);
}

/* ====================================
 * If Pattern Query Methods
 * ==================================== */

/// QueryAllIfPattern
/// \return Get all If Statements that use a variable in conditional container
std::unordered_set<std::string> PKB::QueryAllIfPattern() const {
  return pattern_manager_.GetAllIfPattern();
}

/// QueryIfPattern
/// \param ident
/// \return Get all If Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> PKB::QueryIfPattern(std::string ident) const {
  return pattern_manager_.GetIfPattern(ident);
}

/// QueryPatternVariablesFromIf
/// \param statement_number
/// \return Get all variables used in conditional container of given If
/// Statement
std::unordered_set<std::string> PKB::QueryPatternVariablesFromIf(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromIf(statement_number);
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

std::string PKB::QueryWithAttributeFromStatement(EntityType type,
                                                 int statement_number) const {
  std::string result;
  if (type == EntityType::CALL) {
    result = entity_manager_.GetCallStatementProcedure(statement_number);
  } else if (type == EntityType::PRINT) {
    result = entity_manager_.GetPrintStatementVariable(statement_number);
  } else if (type == EntityType::READ) {
    result = entity_manager_.GetReadStatementVariable(statement_number);
  }
  return result;
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute proc_name or var_name
/// \param identifier proc_name/var_name
/// \return Query entities that matches attribute proc_name or var_name
std::unordered_set<std::string> PKB::QueryWithAttribute(
    EntityType type, AttributeName name, std::string identifier) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::PROCEDURE && name == AttributeName::PROC_NAME) {
    std::unordered_set<std::string> procedures =
        entity_manager_.GetProcedures();
    if (procedures.find(identifier) != procedures.end()) {
      result.emplace(identifier);
    }
  } else if (type == EntityType::CALL && name == AttributeName::PROC_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetCallStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  } else if (type == EntityType::VARIABLE && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> variables = entity_manager_.GetVariables();
    if (variables.find(identifier) != variables.end()) {
      result.emplace(identifier);
    }
  } else if (type == EntityType::READ && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetReadStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  } else if (type == EntityType::PRINT && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetPrintStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  }
  return result;
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute value or stmt_no
/// \param number value/stmt_no
/// \return Query entities that matches attribute value or stmt_no
std::unordered_set<std::string> PKB::QueryWithAttribute(EntityType type,
                                                        AttributeName name,
                                                        int number) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT && name == AttributeName::VALUE) {
    std::unordered_set<std::string> constants = entity_manager_.GetConstants();
    if (constants.find(std::to_string(number)) != constants.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::STATEMENT && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::READ && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetReadStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::PRINT && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetPrintStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::CALL && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetCallStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::WHILE && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetWhileStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::IF && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetIfStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::ASSIGN && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetAssignStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  }
  return result;
}

// Todo: @PKB Team to implement checker
bool PKB::CheckValidAffectsStmtNo(int stmt_no) const { return true || stmt_no; }
