#include "cached_queryable_pkb.h"

CachedQueryablePkb::CachedQueryablePkb(QueryablePkbImpl& queryable_pkb)
    : queryable_pkb_(queryable_pkb) {}

std::unordered_set<std::string> CachedQueryablePkb::QueryAll(
    EntityType type) const {
  return queryable_pkb_.GetEntityQueryable().QueryAll(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollows(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollows(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollowsBy(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollowsBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllFollowsRelations()
    const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryAllFollowsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollows(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollows(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryFollowsTBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetFollowsQueryable()
      .QueryFollowsTBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParent(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParent(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParentBy(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParentBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllParentsRelations()
    const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryAllParentsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParent(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParent(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentT(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentT(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryParentTBy(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetParentQueryable()
      .QueryParentTBy(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllUses(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryAllUses(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllUsesBy(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryAllUsesBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesS(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesS(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesSBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesSBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesP(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesP(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryUsesPBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetUsesQueryable()
      .QueryUsesPBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllModifies(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryAllModifies(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllModifiesBy(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryAllModifiesBy(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesS(
    int statement_number) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesS(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesSBy(
    std::string identifier, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesSBy(identifier, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesP(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesP(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryModifiesPBy(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetModifiesQueryable()
      .QueryModifiesPBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCalls() const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCalls();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCallsBy() const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCallsBy();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllCallsRelations()
    const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryAllCallsRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCalls(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCalls(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsBy(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsT(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsT(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryCallsTBy(
    std::string identifier) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCallsQueryable()
      .QueryCallsTBy(identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllNext(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllNext(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllPrevious(
    EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllPrevious(type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllNextRelations()
    const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryAllNextRelations();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryNext(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryNext(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPrevious(
    int statement_number, EntityType type) const {
  return queryable_pkb_.GetRelationshipQueryablePkb()
      .GetCfgQueryable()
      .QueryPrevious(statement_number, type);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryNextT(
    int statement_number, EntityType type) {
  std::pair<int, EntityType> key = std::make_pair(statement_number, type);
  if (next_t_cache_.find(key) == next_t_cache_.end()) {
    next_t_cache_[key] = queryable_pkb_.GetRelationshipQueryablePkb()
                             .GetCfgQueryable()
                             .QueryNextT(statement_number, type);
  }
  return next_t_cache_[key];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPreviousT(
    int statement_number, EntityType type) {
  std::pair<int, EntityType> key = std::make_pair(statement_number, type);
  if (previous_t_cache_.find(key) == previous_t_cache_.end()) {
    previous_t_cache_[key] = queryable_pkb_.GetRelationshipQueryablePkb()
                                 .GetCfgQueryable()
                                 .QueryPreviousT(statement_number, type);
  }
  return previous_t_cache_[key];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAffects() {
  if (!cached_all_affects_.has_value()) {
    cached_all_affects_ = {queryable_pkb_.GetRelationshipQueryablePkb()
                               .GetAffectsQueryable()
                               .QueryAllAffects()};
  }
  return cached_all_affects_.value();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAffectsBy() {
  if (!cached_all_affects_by_.has_value()) {
    cached_all_affects_by_ = {queryable_pkb_.GetRelationshipQueryablePkb()
                                  .GetAffectsQueryable()
                                  .QueryAllAffectsBy()};
  }
  return cached_all_affects_by_.value();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffects(
    int statement_number) {
  if (affects_stmt_no_cache_.find(statement_number) ==
      affects_stmt_no_cache_.end()) {
    affects_stmt_no_cache_[statement_number] =
        queryable_pkb_.GetRelationshipQueryablePkb()
            .GetAffectsQueryable()
            .QueryAffects(statement_number);
  }
  return affects_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsBy(
    int statement_number) {
  if (affects_by_stmt_no_cache_.find(statement_number) ==
      affects_by_stmt_no_cache_.end()) {
    affects_by_stmt_no_cache_[statement_number] =
        queryable_pkb_.GetRelationshipQueryablePkb()
            .GetAffectsQueryable()
            .QueryAffectsBy(statement_number);
  }
  return affects_by_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsT(
    int statement_number) {
  if (affects_t_stmt_no_cache_.find(statement_number) ==
      affects_t_stmt_no_cache_.end()) {
    affects_t_stmt_no_cache_[statement_number] =
        queryable_pkb_.GetRelationshipQueryablePkb()
            .GetAffectsQueryable()
            .QueryAffectsT(statement_number);
  }
  return affects_t_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAffectsTBy(
    int statement_number) {
  if (affects_t_by_stmt_no_cache_.find(statement_number) ==
      affects_t_by_stmt_no_cache_.end()) {
    affects_t_by_stmt_no_cache_[statement_number] =
        queryable_pkb_.GetRelationshipQueryablePkb()
            .GetAffectsQueryable()
            .QueryAffectsTBy(statement_number);
  }
  return affects_t_by_stmt_no_cache_[statement_number];
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllAssignPattern(
    Expression exp) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryAllAssignPattern(exp);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAssignPattern(
    std::string lhs, Expression exp) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryAssignPattern(lhs, exp);
}

std::unordered_set<std::string>
CachedQueryablePkb::QueryPatternVariablesFromAssign(
    int statement_number) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetAssignPatternQueryable()
      .QueryPatternVariablesFromAssign(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllWhilePattern()
    const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryAllWhilePattern();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWhilePattern(
    std::string ident) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryWhilePattern(ident);
}

std::unordered_set<std::string>
CachedQueryablePkb::QueryPatternVariablesFromWhile(int statement_number) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetWhilePatternQueryable()
      .QueryPatternVariablesFromWhile(statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryAllIfPattern() const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryAllIfPattern();
}

std::unordered_set<std::string> CachedQueryablePkb::QueryIfPattern(
    std::string ident) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryIfPattern(ident);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryPatternVariablesFromIf(
    int statement_number) const {
  return queryable_pkb_.GetPatternQueryablePkb()
      .GetIfPatternQueryable()
      .QueryPatternVariablesFromIf(statement_number);
}

std::string CachedQueryablePkb::QueryWithAttributeFromStatement(
    EntityType type, int statement_number) const {
  return queryable_pkb_.GetEntityQueryable().QueryWithAttributeFromStatement(
      type, statement_number);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWithAttribute(
    EntityType type, AttributeName name, std::string identifier) const {
  return queryable_pkb_.GetEntityQueryable().QueryWithAttribute(type, name,
                                                                identifier);
}

std::unordered_set<std::string> CachedQueryablePkb::QueryWithAttribute(
    EntityType type, AttributeName name, int number) const {
  return queryable_pkb_.GetEntityQueryable().QueryWithAttribute(type, name,
                                                                number);
}

bool CachedQueryablePkb::CheckValidAffectsStmtNo(int stmt_no) const {
  return queryable_pkb_.GetEntityQueryable().CheckValidAffectsStmtNo(stmt_no);
}
