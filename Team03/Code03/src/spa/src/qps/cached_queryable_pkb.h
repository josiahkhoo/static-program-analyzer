#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_CACHED_QUERYABLE_PKB_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_CACHED_QUERYABLE_PKB_H_

#include "common/queryable_pkb.h"

class CachedQueryablePkb : public QueryablePkb {
 public:
  explicit CachedQueryablePkb(QueryablePkb& queryable_pkb);
  std::unordered_set<std::string> QueryAll(EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowsRelations() const override;
  std::unordered_set<std::string> QueryFollows(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsT(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryAllParent(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllParentsRelations() const override;
  std::unordered_set<std::string> QueryParent(int statement_number,
                                              EntityType type) const override;
  std::unordered_set<std::string> QueryParentBy(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryParentT(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryAllUses(EntityType type) const override;
  std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryUsesS(int statement_number,
                                             EntityType type) const override;
  std::unordered_set<std::string> QueryUsesSBy(std::string identifier,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryUsesP(std::string identifier,
                                             EntityType type) const override;
  std::unordered_set<std::string> QueryUsesPBy(std::string identifier,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryModifiesS(
      int statement_number) const override;
  std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const override;
  std::unordered_set<std::string> QueryModifiesP(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryAllCalls() const override;
  std::unordered_set<std::string> QueryAllCallsBy() const override;
  std::unordered_set<std::string> QueryAllCallsRelations() const override;
  std::unordered_set<std::string> QueryCalls(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryCallsBy(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryCallsT(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier) const override;
  std::unordered_set<std::string> QueryAllNext(EntityType type) const override;
  std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllNextRelations() const override;
  std::unordered_set<std::string> QueryNext(int statement_number,
                                            EntityType type) const override;
  std::unordered_set<std::string> QueryPrevious(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryNextT(int statement_number,
                                             EntityType type) const override;
  std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryAllAffects() override;
  std::unordered_set<std::string> QueryAllAffectsBy() override;
  std::unordered_set<std::string> QueryAffects(int statement_number) override;
  std::unordered_set<std::string> QueryAffectsBy(int statement_number) override;
  std::unordered_set<std::string> QueryAffectsT(int statement_number) override;
  std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number) override;
  std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const override;
  std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const override;
  std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int statement_number) const override;
  std::unordered_set<std::string> QueryAllWhilePattern() const override;
  std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const override;
  std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int statement_number) const override;
  std::unordered_set<std::string> QueryAllIfPattern() const override;
  std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const override;
  std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int statement_number) const override;
  std::string QueryWithAttributeFromStatement(
      EntityType type, int statement_number) const override;
  std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name,
      std::string identifier) const override;
  std::unordered_set<std::string> QueryWithAttribute(EntityType type,
                                                     AttributeName name,
                                                     int number) const override;
  bool CheckValidAffectsStmtNo(int stmt_no) const override;

 private:
  QueryablePkb& queryable_pkb_;

  std::unordered_map<int, std::unordered_set<std::string>>
      affects_stmt_no_cache_;
  std::unordered_map<int, std::unordered_set<std::string>>
      affects_by_stmt_no_cache_;
  std::unordered_map<int, std::unordered_set<std::string>>
      affects_t_stmt_no_cache_;
  std::unordered_map<int, std::unordered_set<std::string>>
      affects_t_by_stmt_no_cache_;

  std::optional<std::unordered_set<std::string>> cached_all_affects_;
  std::optional<std::unordered_set<std::string>> cached_all_affects_by_;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_CACHED_QUERYABLE_PKB_H_
