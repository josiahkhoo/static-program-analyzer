#ifndef SPA_PKB_H
#define SPA_PKB_H

#include "common/queryable_pkb.h"
#include "pkb/impl/queryable_pkb_impl.h"
#include "pkb/impl/storable_pkb_impl.h"

class PKB : public QueryablePkb {
 public:
  PKB();

  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType type) const override;
  
  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string>
  QueryAllFollowsRelations() const override;

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string>
  QueryAllParentsRelations() const override;

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int statement_number) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls()
      const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy()
      const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations()
      const override;

  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations()
      const override;

  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int statement_number, EntityType type) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryNextT(
      int statement_number, EntityType type) override;

  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type) override;

  /// QueryAllAffects
  /// \return Query all assign statements that affects some other statement
  [[nodiscard]] std::unordered_set<std::string> QueryAllAffects() override;

  /// QueryAllAffectsBy
  /// \return Query all assign statements that are affected by some other
  /// statement
  [[nodiscard]] std::unordered_set<std::string> QueryAllAffectsBy() override;

  /// QueryAffects
  /// \param statement_number statement
  /// \return Query all assign statements that affects given statement
  [[nodiscard]] std::unordered_set<std::string> QueryAffects(
      int statement_number) override;

  /// QueryAffectsBy
  /// \param statement_number statement
  /// \return Query all assign statements that are affected by given statement
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsBy(
      int statement_number) override;

  /// QueryAffectsT
  /// \param statement_number statement
  /// \return Query all assign statements that affectsT given statement
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsT(
      int statement_number) override;

  /// QueryAffectsTBy
  /// \param statement_number statement
  /// \return Query all assign statements that are affectedT by given statement
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number) override;

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const override;

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const override;

  /// Query pattern variables used in assign statements.
  [[nodiscard]] std::unordered_set<std::string>
  QueryPatternVariablesFromAssign(int statement_number) const override;

  /// Query all while statements that has any patterns.
  [[nodiscard]] std::unordered_set<std::string> QueryAllWhilePattern()
      const override;

  /// Query all while patterns that uses a variable that matches a given
  /// identifier.
  [[nodiscard]] std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const override;

  /// Query pattern variables used in while statements.
  [[nodiscard]] std::unordered_set<std::string>
  QueryPatternVariablesFromWhile(int statement_number) const override;

  /// Query all if statements that has any patterns.
  [[nodiscard]] std::unordered_set<std::string> QueryAllIfPattern()
      const override;

  /// Query all if patterns that uses a variable that matches a given
  /// identifier.
  [[nodiscard]] std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const override;

  /// Query pattern variables used in if statements.
  [[nodiscard]] std::unordered_set<std::string>
  QueryPatternVariablesFromIf(int statement_number) const override;

  /// Query VarName, VarName, ProcName from given Print, Read, Call statement
  /// number respectively
  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType type, int statement_number) const override;

  /// Query entities that matches attribute identifier
  /// Treats x.procName = "name" &  with "name" = x.procName the same
  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, std::string identifier) const override;

  /// Query entities that matches attribute number value or stmt#
  /// Treats x.value = 1 &  with 2 = x.stmt# the same
  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, int number) const override;

  /// Checks with the pkb to see if the given statement number is a read, print,
  /// if, while, or assign statement
  [[nodiscard]] bool CheckValidAffectsStmtNo(int stmt_no) const override;
  
  
  [[nodiscard]] StorablePkbImpl& GetStorablePkbImpl();

//  [[nodiscard]] QueryablePkbImpl& GetQueryablePkbImpl();

 private:
  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
  StorablePkbImpl storable_pkb_impl_;
  QueryablePkbImpl queryable_pkb_impl_;
};

#endif  // SPA_PKB_H
