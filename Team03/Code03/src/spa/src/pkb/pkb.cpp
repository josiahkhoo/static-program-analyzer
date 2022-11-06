#include "pkb.h"

PKB::PKB()
    : storable_pkb_impl_(StorablePkbImpl(entity_manager_, relationship_manager_,
                                         pattern_manager_)),
      queryable_pkb_impl_(QueryablePkbImpl(
          entity_manager_, relationship_manager_, pattern_manager_)) {}

//
///// Store Procedure Entities
///// \param ts List of entities
// void PKB::Store(std::vector<ProcedureEntity> ts) {
//   for (const ProcedureEntity& entity : ts) {
//     entity_manager_.AddProcedure(entity);
//   }
// }
//
///// Store Variable Entities
///// \param ts List of entities
// void PKB::Store(std::vector<VariableEntity> ts) {
//   for (const VariableEntity& entity : ts) {
//     entity_manager_.AddVariable(entity);
//   }
// }
//
///// Store Constant Entities
///// \param ts List of entities
// void PKB::Store(std::vector<ConstantEntity> ts) {
//   for (const ConstantEntity& entity : ts) {
//     entity_manager_.AddConstant(entity);
//   }
// }
//
///// Store Call Entities
///// \param ts List of entities
// void PKB::Store(std::vector<CallEntity> ts) {
//   for (const CallEntity& entity : ts) {
//     entity_manager_.AddCallStatement(entity);
//   }
// }
//
///// Store Read Entities
///// \param ts List of entities
// void PKB::Store(std::vector<ReadEntity> ts) {
//   for (const ReadEntity& entity : ts) {
//     entity_manager_.AddReadStatement(entity);
//   }
// }
//
///// Store Print Entities
///// \param ts List of entities
// void PKB::Store(std::vector<PrintEntity> ts) {
//   for (const PrintEntity& entity : ts) {
//     entity_manager_.AddPrintStatement(entity);
//   }
// }
//
///// Store Assign Entities
///// \param ts List of entities
// void PKB::Store(std::vector<AssignEntity> ts) {
//   for (const AssignEntity& entity : ts) {
//     entity_manager_.AddAssignStatement(entity);
//     pattern_manager_.AddAssignPattern(entity);
//   }
// }
//
///// Store If Entities
///// \param ts List of entities
// void PKB::Store(std::vector<IfEntity> ts) {
//   for (const IfEntity& entity : ts) {
//     entity_manager_.AddIfStatement(entity);
//   }
// }
//
///// Store While Entities
///// \param ts List of entities
// void PKB::Store(std::vector<WhileEntity> ts) {
//   for (const WhileEntity& entity : ts) {
//     entity_manager_.AddWhileStatement(entity);
//   }
// }
//
///// Store Follows Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<FollowsAbstraction> abstractions) {
//   for (const FollowsAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store FollowsT Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<FollowsTAbstraction> abstractions) {
//   for (const FollowsTAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store Parent Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<ParentAbstraction> abstractions) {
//   for (const ParentAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store ParentT Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<ParentTAbstraction> abstractions) {
//   for (const ParentTAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store Calls Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<CallsAbstraction> abstractions) {
//   for (const CallsAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store CallsT Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<CallsTAbstraction> abstractions) {
//   for (const CallsTAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store UsesS Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<UsesSAbstraction> abstractions) {
//   for (const UsesSAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store UsesP Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<UsesPAbstraction> abstractions) {
//   for (const UsesPAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store ModifiesS Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<ModifiesSAbstraction> abstractions) {
//   for (const ModifiesSAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store ModifiesP Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<ModifiesPAbstraction> abstractions) {
//   for (const ModifiesPAbstraction& abstraction : abstractions) {
//     relationship_manager_.AddAbstraction(abstraction);
//   }
// }
//
///// Store While Pattern Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<WhilePatternAbstraction> abstractions) {
//   for (const WhilePatternAbstraction& abstraction : abstractions) {
//     pattern_manager_.AddWhilePattern(abstraction);
//   }
// }
//
///// Store If Pattern Abstractions
///// \param abstractions List of abstractions
// void PKB::Store(std::vector<IfPatternAbstraction> abstractions) {
//   for (const IfPatternAbstraction& abstraction : abstractions) {
//     pattern_manager_.AddIfPattern(abstraction);
//   }
// }
//
///// Store CFGs
///// \param abstractions List of Cfgs
// void PKB::Store(std::vector<CFG> cfgs) {
//   for (const CFG& cfg : cfgs) {
//     relationship_manager_.AddCFG(cfg);
//   }
// }

/// QueryAll
/// \param type
/// \return Query all statements of a specified type
std::unordered_set<std::string> PKB::QueryAll(EntityType type) const {
  return queryable_pkb_impl_.GetEntityQueryable().QueryAll(type);
}

/// QueryAllFollows
/// \param type
/// \return Query all statements following any statement of a specified type
std::unordered_set<std::string> PKB::QueryAllFollows(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollows(type);
}

/// QueryAllFollowsBy
/// \param type
/// \return Query all statements followed by any statement of a specified type
std::unordered_set<std::string> PKB::QueryAllFollowsBy(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollowsBy(type);
}

/// QueryAllFollows
/// \param type
/// \return Gets all statements following or followed by any statement
std::unordered_set<std::string> PKB::QueryAllFollowsRelations() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollowsRelations();
}

/// QueryFollows
/// \param statement_number
/// \param type
/// \return Query all statements directly following a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollows(int statement_number,
                                                  EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollows(statement_number, type);
}

/// QueryFollowsBy
/// \param statement_number
/// \param type
/// \return Query all statements directly followed by a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsBy(int statement_number,
                                                    EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsBy(statement_number, type);
}

/// QueryFollowsT
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsT(int statement_number,
                                                   EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsT(statement_number, type);
}

/// QueryFollowsTBy
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> PKB::QueryFollowsTBy(int statement_number,
                                                     EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsTBy(statement_number, type);
}

/// QueryAllParent
/// \return Query all statements that are direct parents of any statement
std::unordered_set<std::string> PKB::QueryAllParent(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParent(type);
}

/// QueryAllParentBy
/// \return Query all statements that are direct children of any statement
std::unordered_set<std::string> PKB::QueryAllParentBy(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParentBy(type);
}

/// QueryAllParentsRelations
/// \return Query all parent and children statements of any statement
std::unordered_set<std::string> PKB::QueryAllParentsRelations() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParentsRelations();
}

/// QueryParent
/// \param statement_number
/// \param type
/// \return Query all statements that are direct parents of a specified
/// statement
std::unordered_set<std::string> PKB::QueryParent(int statement_number,
                                                 EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParent(statement_number, type);
}

/// QueryParentBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> PKB::QueryParentBy(int statement_number,
                                                   EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentBy(statement_number, type);
}

/// QueryParentT
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> PKB::QueryParentT(int statement_number,
                                                  EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentT(statement_number, type);
}

/// QueryParentTBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> PKB::QueryParentTBy(int statement_number,
                                                    EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentTBy(statement_number, type);
}

/* ====================================
 * Uses Query Methods
 * ==================================== */

/// QueryAllUses
/// \param type
/// \return All statements or procedures that uses some Variable
std::unordered_set<std::string> PKB::QueryAllUses(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryAllUses(type);
}

/// QueryAllUsesBy
/// \param type
/// \return All Variables that are used by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> PKB::QueryAllUsesBy(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryAllUsesBy(type);
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified statement
std::unordered_set<std::string> PKB::QueryUsesS(int statement_number,
                                                EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesS(statement_number, type);
}

/// QueryUsesSBy
/// \param identifier
/// \param type
/// \return Query all statements that use a specified variable
std::unordered_set<std::string> PKB::QueryUsesSBy(std::string identifier,
                                                  EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesSBy(identifier, type);
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified procedure
std::unordered_set<std::string> PKB::QueryUsesP(std::string identifier,
                                                EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesP(identifier, type);
}

/// QueryUsesPBy
/// \param identifier
/// \param type
/// \return Query all procedures that use a specified variable
std::unordered_set<std::string> PKB::QueryUsesPBy(std::string identifier,
                                                  EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesPBy(identifier, type);
}

/* ====================================
 * Modifies Query Methods
 * ==================================== */

/// QueryAllModifies
/// \param type
/// \return All statements or procedures that modifies some Variable
std::unordered_set<std::string> PKB::QueryAllModifies(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryAllModifies(type);
}

/// QueryAllModifiesBy
/// \param type
/// \return All Variables that are modified by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> PKB::QueryAllModifiesBy(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryAllModifiesBy(type);
}

/// QueryModifiesS
/// \param statement_number
/// \return Variables modified in given statement_number
std::unordered_set<std::string> PKB::QueryModifiesS(
    int statement_number) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesS(statement_number);
}

/// QueryModifiesSBy
/// \param identifier
/// \param type
/// \return Statements that modifies given Variable identifier
std::unordered_set<std::string> PKB::QueryModifiesSBy(std::string identifier,
                                                      EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesSBy(identifier, type);
}

/// QueryModifiesP
/// \param identifier
/// \return Variables modified in given Procedure identifier
std::unordered_set<std::string> PKB::QueryModifiesP(
    std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesP(identifier);
}

/// QueryModifiesPBy
/// \param identifier
/// \return Procedures that modifies given Variable identifier
std::unordered_set<std::string> PKB::QueryModifiesPBy(
    std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesPBy(identifier);
}

/* ====================================
 * Calls Query Methods
 * ==================================== */
/// QueryAllCalls
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> PKB::QueryAllCalls() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCalls();
}

/// QueryAllCallsBy
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> PKB::QueryAllCallsBy() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCallsBy();
}

/// QueryAllCallsBy
/// \return Query all procedures that call or are called by any procedure
std::unordered_set<std::string> PKB::QueryAllCallsRelations() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCallsRelations();
}

/// QueryCalls
/// \param identifier
/// \return Gets all procedures that directly call a specified procedure
std::unordered_set<std::string> PKB::QueryCalls(std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCalls(identifier);
}

/// QueryCallsBy
/// \param identifier
/// \return Gets all procedures that are directly called by a specified
/// procedure
std::unordered_set<std::string> PKB::QueryCallsBy(
    std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsBy(identifier);
}

/// QueryCallsT
/// \param identifier
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
std::unordered_set<std::string> PKB::QueryCallsT(std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsT(identifier);
}

/// QueryCallsTBy
/// \param identifier
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
std::unordered_set<std::string> PKB::QueryCallsTBy(
    std::string identifier) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsTBy(identifier);
}

/* ====================================
 * Next Query Methods
 * ==================================== */
/// QueryAllNext
/// \return Query all statements that come next to some statement
std::unordered_set<std::string> PKB::QueryAllNext(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllNext(type);
}

/// QueryAllPrevious
/// \return Query all statements that come previous to some statement
std::unordered_set<std::string> PKB::QueryAllPrevious(EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllPrevious(type);
}

/// QueryAllNext
/// \return Query all statements that come next or previous to some statement
std::unordered_set<std::string> PKB::QueryAllNextRelations() const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllNextRelations();
}

/// QueryNext
/// \param statement_number statement
/// \return Query statement(s) that immediately comes next after given statement
std::unordered_set<std::string> PKB::QueryNext(int statement_number,
                                               EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryNext(statement_number, type);
}

/// QueryPrevious
/// \param statement_number statement
/// \return Query statement(s) that immediately comes previous before given
/// statement
std::unordered_set<std::string> PKB::QueryPrevious(int statement_number,
                                                   EntityType type) const {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryPrevious(statement_number, type);
}

/// QueryNextT
/// \param statement_number statement
/// \return Query statement(s) that comes nextT after given statement
std::unordered_set<std::string> PKB::QueryNextT(int statement_number,
                                                EntityType type) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryNextT(statement_number, type);
}

/// QueryPreviousT
/// \param statement_number statement
/// \return Query statement(s) that comes previousT before given statement
std::unordered_set<std::string> PKB::QueryPreviousT(int statement_number,
                                                    EntityType type) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryPreviousT(statement_number, type);
}

/* ====================================
 * Affects Query Methods
 * ==================================== */

/// QueryAllAffects
/// \return Query all assign statements that affects some other statement
std::unordered_set<std::string> PKB::QueryAllAffects() {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAllAffects();
}

/// QueryAllAffectsBy
/// \return Query all assign statements that are affected by some other
/// statement
std::unordered_set<std::string> PKB::QueryAllAffectsBy() {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAllAffectsBy();
}

/// QueryAffects
/// \param statement_number statement
/// \return Query all assign statements that affects given statement
std::unordered_set<std::string> PKB::QueryAffects(int statement_number) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAffects(statement_number);
}

/// QueryAffectsBy
/// \param statement_number statement
/// \return Query all assign statements that are affected by given statement
std::unordered_set<std::string> PKB::QueryAffectsBy(int statement_number) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAffectsBy(statement_number);
}

/// QueryAffectsT
/// \param statement_number statement
/// \return Query all assign statements that affectsT given statement
std::unordered_set<std::string> PKB::QueryAffectsT(int statement_number) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAffectsT(statement_number);
}

/// QueryAffectsTBy
/// \param statement_number statement
/// \return Query all assign statements that are affectedT by given statement
std::unordered_set<std::string> PKB::QueryAffectsTBy(int statement_number) {
  return queryable_pkb_impl_.GetRelationshipQueryablePkb()
      .GetAffectsQueryable()
      .QueryAffectsTBy(statement_number);
}

/* ====================================
 * Assign Pattern Query Methods
 * ==================================== */

std::unordered_set<std::string> PKB::QueryAllAssignPattern(
    Expression exp) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryAllAssignPattern(exp);
}

std::unordered_set<std::string> PKB::QueryAssignPattern(std::string lhs,
                                                        Expression exp) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryAssignPattern(lhs, exp);
}

std::unordered_set<std::string> PKB::QueryPatternVariablesFromAssign(
    int statement_number) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryPatternVariablesFromAssign(statement_number);
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

/// QueryAllWhilePattern
/// \return Get all While Statements that use a variable in conditional
/// container
std::unordered_set<std::string> PKB::QueryAllWhilePattern() const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryAllWhilePattern();
}

/// QueryWhilePattern
/// \param ident
/// \return Get all While Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> PKB::QueryWhilePattern(
    std::string ident) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryWhilePattern(ident);
}

/// QueryPatternVariablesFromWhile
/// \param statement_number
/// \return Get all variables used in conditional container of given While
/// Statement
std::unordered_set<std::string> PKB::QueryPatternVariablesFromWhile(
    int statement_number) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryPatternVariablesFromWhile(statement_number);
}

/* ====================================
 * If Pattern Query Methods
 * ==================================== */

/// QueryAllIfPattern
/// \return Get all If Statements that use a variable in conditional container
std::unordered_set<std::string> PKB::QueryAllIfPattern() const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryAllIfPattern();
}

/// QueryIfPattern
/// \param ident
/// \return Get all If Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> PKB::QueryIfPattern(std::string ident) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryIfPattern(ident);
}

/// QueryPatternVariablesFromIf
/// \param statement_number
/// \return Get all variables used in conditional container of given If
/// Statement
std::unordered_set<std::string> PKB::QueryPatternVariablesFromIf(
    int statement_number) const {
  return queryable_pkb_impl_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryPatternVariablesFromIf(statement_number);
}

/* ====================================
 * While Pattern Query Methods
 * ==================================== */

std::string PKB::QueryWithAttributeFromStatement(EntityType type,
                                                 int statement_number) const {
  return queryable_pkb_impl_.GetEntityQueryable()
      .QueryWithAttributeFromStatement(type, statement_number);
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute proc_name or var_name
/// \param identifier proc_name/var_name
/// \return Query entities that matches attribute proc_name or var_name
std::unordered_set<std::string> PKB::QueryWithAttribute(
    EntityType type, AttributeName name, std::string identifier) const {
  return queryable_pkb_impl_.GetEntityQueryable().QueryWithAttribute(
      type, name, identifier);
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute value or stmt_no
/// \param number value/stmt_no
/// \return Query entities that matches attribute value or stmt_no
std::unordered_set<std::string> PKB::QueryWithAttribute(EntityType type,
                                                        AttributeName name,
                                                        int number) const {
  return queryable_pkb_impl_.GetEntityQueryable().QueryWithAttribute(type, name,
                                                                     number);
}

bool PKB::CheckValidAffectsStmtNo(int stmt_no) const {
  return queryable_pkb_impl_.GetEntityQueryable().CheckValidAffectsStmtNo(
      stmt_no);
}

StorablePkbImpl& PKB::GetStorablePkbImpl() { return storable_pkb_impl_; }
