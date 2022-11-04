#include "cached_queryable_pkb.h"

CachedQueryablePkb::CachedQueryablePkb(QueryablePkb& queryable_pkb)
    : queryable_pkb_(queryable_pkb) {}

std::unordered_set<std::string> CachedQueryablePkb::QueryAll(
    EntityType type) const {
  return queryable_pkb_.QueryAll(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollows(
    EntityType type) const {
  return queryable_pkb_.QueryAllFollows(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollowsBy(
    EntityType type) const {
  return queryable_pkb_.QueryAllFollowsBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollowsRelations()
    const {
  return queryable_pkb_.QueryAllFollowsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollows(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryFollows(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryFollowsBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryFollowsT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsTBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryFollowsTBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParent(
    EntityType type) const {
  return queryable_pkb_.QueryAllParent(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParentBy(
    EntityType type) const {
  return queryable_pkb_.QueryAllParentBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParentsRelations()
    const {
  return queryable_pkb_.QueryAllParentsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParent(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryParent(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryParentBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryParentT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentTBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryParentTBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllUses(
    EntityType type) const {
  return queryable_pkb_.QueryAllUses(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllUsesBy(
    EntityType type) const {
  return queryable_pkb_.QueryAllUsesBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesS(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryUsesS(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesSBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.QueryUsesSBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesP(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.QueryUsesP(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesPBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.QueryUsesPBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllModifies(
    EntityType type) const {
  return queryable_pkb_.QueryAllModifies(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllModifiesBy(
    EntityType type) const {
  return queryable_pkb_.QueryAllModifiesBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesS(
    int statement_number) const {
  return queryable_pkb_.QueryModifiesS(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesSBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.QueryModifiesSBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesP(
    std::string identifier) const {
  return queryable_pkb_.QueryModifiesP(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesPBy(
    std::string identifier) const {
  return queryable_pkb_.QueryModifiesPBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCalls() const {
  return queryable_pkb_.QueryAllCalls();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCallsBy() const {
  return queryable_pkb_.QueryAllCallsBy();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCallsRelations()
    const {
  return queryable_pkb_.QueryAllCallsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCalls(
    std::string identifier) const {
  return queryable_pkb_.QueryCalls(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsBy(
    std::string identifier) const {
  return queryable_pkb_.QueryCallsBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsT(
    std::string identifier) const {
  return queryable_pkb_.QueryCallsT(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsTBy(
    std::string identifier) const {
  return queryable_pkb_.QueryCallsTBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllNext(
    EntityType type) const {
  return queryable_pkb_.QueryAllNext(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllPrevious(
    EntityType type) const {
  return queryable_pkb_.QueryAllPrevious(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllNextRelations()
    const {
  return queryable_pkb_.QueryAllNextRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryNext(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryNext(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPrevious(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryPrevious(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryNextT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryNextT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPreviousT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.QueryPreviousT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAffects() {
  if (cached_all_affects_->empty()) {
    cached_all_affects_ = queryable_pkb_.QueryAllAffects();
  }
  return cached_all_affects_.value();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAffectsBy() {
  if (cached_all_affects_by_->empty()) {
    cached_all_affects_by_ = queryable_pkb_.QueryAllAffectsBy();
  }
  return cached_all_affects_by_.value();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffects(
    int statement_number) {
  if (affects_stmt_no_cache_.find(statement_number) !=
      affects_stmt_no_cache_.end()) {
    affects_stmt_no_cache_[statement_number] =
        queryable_pkb_.QueryAffects(statement_number);
  }
  return affects_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsBy(
    int statement_number) {
  if (affects_by_stmt_no_cache_.find(statement_number) !=
      affects_by_stmt_no_cache_.end()) {
    affects_by_stmt_no_cache_[statement_number] =
        queryable_pkb_.QueryAffectsBy(statement_number);
  }
  return affects_by_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsT(
    int statement_number) {
  if (affects_t_stmt_no_cache_.find(statement_number) !=
      affects_t_stmt_no_cache_.end()) {
    affects_t_stmt_no_cache_[statement_number] =
        queryable_pkb_.QueryAffectsT(statement_number);
  }
  return affects_t_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsTBy(
    int statement_number) {
  if (affects_t_by_stmt_no_cache_.find(statement_number) !=
      affects_t_by_stmt_no_cache_.end()) {
    affects_t_by_stmt_no_cache_[statement_number] =
        queryable_pkb_.QueryAffectsTBy(statement_number);
  }
  return affects_t_by_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAssignPattern(
    Expression exp) const {
  return queryable_pkb_.QueryAllAssignPattern(exp);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAssignPattern(
    std::string lhs, Expression exp) const {
  return queryable_pkb_.QueryAssignPattern(lhs, exp);
}

std::unordered_set<std::string>
CachedQueryablePkb::QueryPatternVariablesFromAssign(
    int statement_number) const {
  return queryable_pkb_.QueryPatternVariablesFromAssign(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllWhilePattern()
    const {
  return queryable_pkb_.QueryAllWhilePattern();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWhilePattern(
    std::string ident) const {
  return queryable_pkb_.QueryWhilePattern(ident);
}

std::unordered_set<std::string>
CachedQueryablePkb::QueryPatternVariablesFromWhile(int statement_number) const {
  return queryable_pkb_.QueryPatternVariablesFromWhile(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllIfPattern() const {
  return queryable_pkb_.QueryAllIfPattern();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryIfPattern(
    std::string ident) const {
  return queryable_pkb_.QueryIfPattern(ident);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPatternVariablesFromIf(
    int statement_number) const {
  return queryable_pkb_.QueryPatternVariablesFromIf(statement_number);
}

std::string CachedQueryablePkb::QueryWithAttributeFromStatement(
    EntityType type, int statement_number) const {
  return queryable_pkb_.QueryWithAttributeFromStatement(type, statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWithAttribute(
    EntityType type, AttributeName name, std::string identifier) const {
  return queryable_pkb_.QueryWithAttribute(type, name, identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWithAttribute(
    EntityType type, AttributeName name, int number) const {
  return queryable_pkb_.QueryWithAttribute(type, name, number);
}

bool CachedQueryablePkb::CheckValidAffectsStmtNo(int stmt_no) const {
  return queryable_pkb_.CheckValidAffectsStmtNo(stmt_no);
}
