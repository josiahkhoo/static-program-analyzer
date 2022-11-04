#include "pkb.h"

#include <stdexcept>
#include <vector>

#include "common/reference/attribute_name.h"

template <class T>
PKB<T>::PKB() {}
//
///// Store Procedure Entities
///// \param ts List of entities
//void PKB::Store(std::vector<ProcedureEntity> ts) {
//  for (const ProcedureEntity& entity : ts) {
//    entity_manager_.AddProcedure(entity);
//  }
//}
//
///// Store Variable Entities
///// \param ts List of entities
//void PKB::Store(std::vector<VariableEntity> ts) {
//  for (const VariableEntity& entity : ts) {
//    entity_manager_.AddVariable(entity);
//  }
//}
//
///// Store Constant Entities
///// \param ts List of entities
//void PKB::Store(std::vector<ConstantEntity> ts) {
//  for (const ConstantEntity& entity : ts) {
//    entity_manager_.AddConstant(entity);
//  }
//}
//
///// Store Call Entities
///// \param ts List of entities
//void PKB::Store(std::vector<CallEntity> ts) {
//  for (const CallEntity& entity : ts) {
//    entity_manager_.AddCallStatement(entity);
//  }
//}
//
///// Store Read Entities
///// \param ts List of entities
//void PKB::Store(std::vector<ReadEntity> ts) {
//  for (const ReadEntity& entity : ts) {
//    entity_manager_.AddReadStatement(entity);
//  }
//}
//
///// Store Print Entities
///// \param ts List of entities
//void PKB::Store(std::vector<PrintEntity> ts) {
//  for (const PrintEntity& entity : ts) {
//    entity_manager_.AddPrintStatement(entity);
//  }
//}
//
///// Store Assign Entities
///// \param ts List of entities
//void PKB::Store(std::vector<AssignEntity> ts) {
//  for (const AssignEntity& entity : ts) {
//    entity_manager_.AddAssignStatement(entity);
//    pattern_manager_.AddAssignPattern(entity);
//  }
//}
//
///// Store If Entities
///// \param ts List of entities
//void PKB::Store(std::vector<IfEntity> ts) {
//  for (const IfEntity& entity : ts) {
//    entity_manager_.AddIfStatement(entity);
//  }
//}
//
///// Store While Entities
///// \param ts List of entities
//void PKB::Store(std::vector<WhileEntity> ts) {
//  for (const WhileEntity& entity : ts) {
//    entity_manager_.AddWhileStatement(entity);
//  }
//}
//
///// Store Follows Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<FollowsAbstraction> abstractions) {
//  for (const FollowsAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store FollowsT Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<FollowsTAbstraction> abstractions) {
//  for (const FollowsTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store Parent Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<ParentAbstraction> abstractions) {
//  for (const ParentAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ParentT Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<ParentTAbstraction> abstractions) {
//  for (const ParentTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store Calls Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<CallsAbstraction> abstractions) {
//  for (const CallsAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store CallsT Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<CallsTAbstraction> abstractions) {
//  for (const CallsTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store UsesS Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<UsesSAbstraction> abstractions) {
//  for (const UsesSAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store UsesP Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<UsesPAbstraction> abstractions) {
//  for (const UsesPAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ModifiesS Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<ModifiesSAbstraction> abstractions) {
//  for (const ModifiesSAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ModifiesP Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<ModifiesPAbstraction> abstractions) {
//  for (const ModifiesPAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store While Pattern Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<WhilePatternAbstraction> abstractions) {
//  for (const WhilePatternAbstraction& abstraction : abstractions) {
//    pattern_manager_.AddWhilePattern(abstraction);
//  }
//}
//
///// Store If Pattern Abstractions
///// \param abstractions List of abstractions
//void PKB::Store(std::vector<IfPatternAbstraction> abstractions) {
//  for (const IfPatternAbstraction& abstraction : abstractions) {
//    pattern_manager_.AddIfPattern(abstraction);
//  }
//}
//
///// Store CFGs
///// \param abstractions List of Cfgs
//void PKB::Store(std::vector<CFG> cfgs) {
//  for (const CFG& cfg : cfgs) {
//    relationship_manager_.AddCFG(cfg);
//  }
//}

/// QueryAll
/// \param type
/// \return Query all statements of a specified type
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAll(EntityType type) const {
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
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllFollows(EntityType type) const {
  return FindIntersect(relationship_manager_.GetFollowsStatements(),
                       QueryAll(type));
}

/// QueryAllFollowsBy
/// \param type
/// \return Query all statements followed by any statement of a specified type
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllFollowsBy(EntityType type) const {
  return FindIntersect(relationship_manager_.GetFollowsByStatements(),
                       QueryAll(type));
}

/// QueryAllFollows
/// \param type
/// \return Gets all statements following or followed by any statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllFollowsRelations() const {
  return relationship_manager_.GetFollowsStatements();
}

/// QueryFollows
/// \param statement_number
/// \param type
/// \return Query all statements directly following a specified
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryFollows(int statement_number,
                                                  EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsStatements(statement_number),
      QueryAll(type));
}

/// QueryFollowsBy
/// \param statement_number
/// \param type
/// \return Query all statements directly followed by a specified
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryFollowsBy(int statement_number,
                                                    EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsByStatements(statement_number),
      QueryAll(type));
}

/// QueryFollowsT
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly following a specified
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryFollowsT(int statement_number,
                                                   EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsTStatements(statement_number),
      QueryAll(type));
}

/// QueryFollowsTBy
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly followed by a specified
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryFollowsTBy(int statement_number,
                                                     EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsTByStatements(statement_number),
      QueryAll(type));
}

/// QueryAllParent
/// \return Query all statements that are direct parents of any statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllParent(EntityType type) const {
  return FindIntersect(relationship_manager_.GetParentStatements(),
                       QueryAll(type));
}

/// QueryAllParentBy
/// \return Query all statements that are direct children of any statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllParentBy(EntityType type) const {
  return FindIntersect(relationship_manager_.GetParentByStatements(),
                       QueryAll(type));
}

/// QueryAllParentsRelations
/// \return Query all parent and children statements of any statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllParentsRelations() const {
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
template <class T>
std::unordered_set<std::string> PKB<T>::QueryParent(int statement_number,
                                                 EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentStatements(statement_number),
      QueryAll(type));
}

/// QueryParentBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct children of a specified
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryParentBy(int statement_number,
                                                   EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentByStatements(statement_number),
      QueryAll(type));
}

/// QueryParentT
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect parents of a
/// specified statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryParentT(int statement_number,
                                                  EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentTStatements(statement_number),
      QueryAll(type));
}

/// QueryParentTBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect children of a
/// specified statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryParentTBy(int statement_number,
                                                    EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentTByStatements(statement_number),
      QueryAll(type));
}

/* ====================================
 * Uses Query Methods
 * ==================================== */

/// QueryAllUses
/// \param type
/// \return All statements or procedures that uses some Variable
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllUses(EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetUsingProcedures();
  } else {
    return FindIntersect(relationship_manager_.GetUsingStatements(),
                         QueryAll(type));
  }
}

/// QueryAllUsesBy
/// \param type
/// \return All Variables that are used by EntityType (Procedure or
/// Statement types)
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllUsesBy(EntityType type) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    result = {};
  } else if (type == EntityType::PROCEDURE) {
    result = relationship_manager_.GetVariablesUsedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    result = relationship_manager_.GetVariablesUsedByStatements();
  } else {
    std::unordered_set<std::string> typed_statements = QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesUsedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
  }
  return result;
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryUsesS(int statement_number,
                                                EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetVariablesUsedByStatement(statement_number),
      QueryAll(type));
}

/// QueryUsesSBy
/// \param identifier
/// \param type
/// \return Query all statements that use a specified variable
template <class T>
std::unordered_set<std::string> PKB<T>::QueryUsesSBy(std::string identifier,
                                                  EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetStatementsUsingVariable(identifier),
      QueryAll(type));
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryUsesP(std::string identifier,
                                                EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetVariablesUsedByProcedure(identifier),
      QueryAll(type));
}

/// QueryUsesPBy
/// \param identifier
/// \param type
/// \return Query all procedures that use a specified variable
template <class T>
std::unordered_set<std::string> PKB<T>::QueryUsesPBy(std::string identifier,
                                                  EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetProceduresUsingVariable(identifier),
      QueryAll(type));
}

/* ====================================
 * Modifies Query Methods
 * ==================================== */

/// QueryAllModifies
/// \param type
/// \return All statements or procedures that modifies some Variable
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllModifies(EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetModifyingProcedures();
  } else {
    return FindIntersect(relationship_manager_.GetModifyingStatements(),
                         QueryAll(type));
  }
}

/// QueryAllModifiesBy
/// \param type
/// \return All Variables that are modified by EntityType (Procedure or
/// Statement types)
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllModifiesBy(EntityType type) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    result = {};
  } else if (type == EntityType::PROCEDURE) {
    result = relationship_manager_.GetVariablesModifiedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    result = relationship_manager_.GetVariablesModifiedByStatements();
  } else {
    std::unordered_set<std::string> typed_statements = QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesModifiedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
  }
  return result;
}

/// QueryModifiesS
/// \param statement_number
/// \return Variables modified in given statement_number
template <class T>
std::unordered_set<std::string> PKB<T>::QueryModifiesS(
    int statement_number) const {
  return relationship_manager_.GetVariablesModifiedByStatement(
      statement_number);
}

/// QueryModifiesSBy
/// \param identifier
/// \param type
/// \return Statements that modifies given Variable identifier
template <class T>
std::unordered_set<std::string> PKB<T>::QueryModifiesSBy(std::string identifier,
                                                      EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetStatementsModifyingVariable(identifier),
      QueryAll(type));
}

/// QueryModifiesP
/// \param identifier
/// \return Variables modified in given Procedure identifier
template <class T>
std::unordered_set<std::string> PKB<T>::QueryModifiesP(
    std::string identifier) const {
  return relationship_manager_.GetVariablesModifiedByProcedure(identifier);
}

/// QueryModifiesPBy
/// \param identifier
/// \return Procedures that modifies given Variable identifier
template <class T>
std::unordered_set<std::string> PKB<T>::QueryModifiesPBy(
    std::string identifier) const {
  return relationship_manager_.GetProceduresModifyingVariable(identifier);
}

/* ====================================
 * Calls Query Methods
 * ==================================== */
/// QueryAllCalls
/// \return Query all procedures that call any procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllCalls() const {
  return relationship_manager_.GetCallsProcedures();
}

/// QueryAllCallsBy
/// \return Query all procedures that call any procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllCallsBy() const {
  return relationship_manager_.GetCallsByProcedures();
}

/// QueryAllCallsBy
/// \return Query all procedures that call or are called by any procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllCallsRelations() const {
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
template <class T>
std::unordered_set<std::string> PKB<T>::QueryCalls(std::string identifier) const {
  return relationship_manager_.GetCallsProcedures(identifier);
}

/// QueryCallsBy
/// \param identifier
/// \return Gets all procedures that are directly called by a specified
/// procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryCallsBy(
    std::string identifier) const {
  return relationship_manager_.GetCallsByProcedures(identifier);
}

/// QueryCallsT
/// \param identifier
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryCallsT(std::string identifier) const {
  return relationship_manager_.GetCallsTProcedures(identifier);
}

/// QueryCallsTBy
/// \param identifier
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
template <class T>
std::unordered_set<std::string> PKB<T>::QueryCallsTBy(
    std::string identifier) const {
  return relationship_manager_.GetCallsTByProcedures(identifier);
}

/* ====================================
 * Next Query Methods
 * ==================================== */
/// QueryAllNext
/// \return Query all statements that come next to some statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllNext(EntityType type) const {
  return FindIntersect(relationship_manager_.GetAllNext(), QueryAll(type));
}

/// QueryAllPrevious
/// \return Query all statements that come previous to some statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllPrevious(EntityType type) const {
  return FindIntersect(relationship_manager_.GetAllPrevious(), QueryAll(type));
}

/// QueryAllNext
/// \return Query all statements that come next or previous to some statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllNextRelations() const {
  std::unordered_set<std::string> result = relationship_manager_.GetAllNext();
  std::unordered_set<std::string> previous =
      relationship_manager_.GetAllPrevious();
  result.merge(previous);
  return result;
}

/// QueryNext
/// \param statement_number statement
/// \return Query statement(s) that immediately comes next after given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryNext(int statement_number,
                                               EntityType type) const {
  return FindIntersect(relationship_manager_.GetNext(statement_number),
                       QueryAll(type));
}

/// QueryPrevious
/// \param statement_number statement
/// \return Query statement(s) that immediately comes previous before given
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryPrevious(int statement_number,
                                                   EntityType type) const {
  return FindIntersect(relationship_manager_.GetPrevious(statement_number),
                       QueryAll(type));
}

/// QueryNextT
/// \param statement_number statement
/// \return Query statement(s) that comes nextT after given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryNextT(int statement_number,
                                                EntityType type) const {
  return FindIntersect(relationship_manager_.GetNextT(statement_number),
                       QueryAll(type));
}

/// QueryPreviousT
/// \param statement_number statement
/// \return Query statement(s) that comes previousT before given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryPreviousT(int statement_number,
                                                    EntityType type) const {
  return FindIntersect(relationship_manager_.GetPreviousT(statement_number),
                       QueryAll(type));
}

/* ====================================
 * Affects Query Methods
 * ==================================== */

/// QueryAllAffects
/// \return Query all assign statements that affects some other statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllAffects() const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAllAffects(assigns, calls, reads);
}

/// QueryAllAffectsBy
/// \return Query all assign statements that are affected by some other
/// statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllAffectsBy() const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  return relationship_manager_.GetAllAffectsBy(assigns, calls, reads);
}

/// QueryAffects
/// \param statement_number statement
/// \return Query all assign statements that affects given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAffects(int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  if (CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffects(assigns, calls, reads,
                                          statement_number);
}

/// QueryAffectsBy
/// \param statement_number statement
/// \return Query all assign statements that are affected by given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAffectsBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  if (CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsBy(assigns, calls, reads,
                                            statement_number);
}

/// QueryAffectsT
/// \param statement_number statement
/// \return Query all assign statements that affectsT given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAffectsT(int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  if (CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsT(assigns, calls, reads,
                                           statement_number);
}

/// QueryAffectsTBy
/// \param statement_number statement
/// \return Query all assign statements that are affectedT by given statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAffectsTBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  if (CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsTBy(assigns, calls, reads,
                                             statement_number);
}

/* ====================================
 * Assign Pattern Query Methods
 * ==================================== */

template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllAssignPattern(
    Expression exp) const {
  return pattern_manager_.GetAllPattern(exp);
}

template <class T>
std::unordered_set<std::string> PKB<T>::QueryAssignPattern(std::string lhs,
                                                        Expression exp) const {
  return pattern_manager_.GetPattern(lhs, exp);
}

template <class T>
std::unordered_set<std::string> PKB<T>::QueryPatternVariablesFromAssign(
    int) const {
  return {};
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

/// QueryAllWhilePattern
/// \return Get all While Statements that use a variable in conditional
/// container
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllWhilePattern() const {
  return pattern_manager_.GetAllWhilePattern();
}

/// QueryWhilePattern
/// \param ident
/// \return Get all While Statements that use variable ident in conditional
/// container
template <class T>
std::unordered_set<std::string> PKB<T>::QueryWhilePattern(
    std::string ident) const {
  return pattern_manager_.GetWhilePattern(ident);
}

/// QueryPatternVariablesFromWhile
/// \param statement_number
/// \return Get all variables used in conditional container of given While
/// Statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryPatternVariablesFromWhile(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromWhile(statement_number);
}

/* ====================================
 * If Pattern Query Methods
 * ==================================== */

/// QueryAllIfPattern
/// \return Get all If Statements that use a variable in conditional container
template <class T>
std::unordered_set<std::string> PKB<T>::QueryAllIfPattern() const {
  return pattern_manager_.GetAllIfPattern();
}

/// QueryIfPattern
/// \param ident
/// \return Get all If Statements that use variable ident in conditional
/// container
template <class T>
std::unordered_set<std::string> PKB<T>::QueryIfPattern(std::string ident) const {
  return pattern_manager_.GetIfPattern(ident);
}

/// QueryPatternVariablesFromIf
/// \param statement_number
/// \return Get all variables used in conditional container of given If
/// Statement
template <class T>
std::unordered_set<std::string> PKB<T>::QueryPatternVariablesFromIf(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromIf(statement_number);
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

template <class T>
std::string PKB<T>::QueryWithAttributeFromStatement(EntityType type,
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
template <class T>
std::unordered_set<std::string> PKB<T>::QueryWithAttribute(
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
template <class T>
std::unordered_set<std::string> PKB<T>::QueryWithAttribute(EntityType type,
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

template <class T>
bool PKB<T>::CheckValidAffectsStmtNo(int stmt_no) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> ifs = entity_manager_.GetIfStatements();
  std::unordered_set<std::string> whiles = entity_manager_.GetWhileStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  std::unordered_set<std::string> prints = entity_manager_.GetPrintStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  if (assigns.find(std::to_string(stmt_no)) != assigns.end()) {
    return true;
  } else if (ifs.find(std::to_string(stmt_no)) != ifs.end()) {
    return true;
  } else if (whiles.find(std::to_string(stmt_no)) != whiles.end()) {
    return true;
  } else if (reads.find(std::to_string(stmt_no)) != reads.end()) {
    return true;
  } else if (prints.find(std::to_string(stmt_no)) != prints.end()) {
    return true;
  } else if (calls.find(std::to_string(stmt_no)) != calls.end()) {
    return true;
  }
  return false;
}

template <class T>
bool PKB<T>::CheckNotAssignStmtNo(int stmt_no) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  if (assigns.find(std::to_string(stmt_no)) != assigns.end()) {
    return false;
  }
  return true;
}

/// FindIntersect
/// \param statements Statements from relationship manager
/// \param typed_statements Statements from entity manager
/// \return Statements that are in both sets of statements
template <class T>
std::unordered_set<std::string> PKB<T>::FindIntersect(
    std::unordered_set<std::string> statements,
    std::unordered_set<std::string> typed_statements) const {
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}