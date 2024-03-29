#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/reference/attribute.h"
#include "common/reference/expression.h"

class QueryablePkb {
 public:
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAll(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryAllFollowsRelations() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllParent(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryAllParentsRelations() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllUses(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesS(
      int statement_number) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesP(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCalls()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCallsBy()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCallsRelations()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCalls(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsBy(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsT(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllNext(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllNextRelations()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryNext(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryPrevious(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryNextT(
      int statement_number, EntityType type) = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type) = 0;

  /// QueryAllAffects
  /// \return Query all assign statements that affects some other statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllAffects() = 0;

  /// QueryAllAffectsBy
  /// \return Query all assign statements that are affected by some other
  /// statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllAffectsBy() = 0;

  /// QueryAffects
  /// \param statement_number statement
  /// \return Query all assign statements that affects given statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffects(
      int statement_number) = 0;

  /// QueryAffectsBy
  /// \param statement_number statement
  /// \return Query all assign statements that are affected by given statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsBy(
      int statement_number) = 0;

  /// QueryAffectsT
  /// \param statement_number statement
  /// \return Query all assign statements that affectsT given statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsT(
      int statement_number) = 0;

  /// QueryAffectsTBy
  /// \param statement_number statement
  /// \return Query all assign statements that are affectedT by given statement
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number) = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const = 0;

  /// Query pattern variables used in assign statements.
  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryPatternVariablesFromAssign(int statement_number) const = 0;

  /// Query all while statements that has any patterns.
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllWhilePattern()
      const = 0;

  /// Query all while patterns that uses a variable that matches a given
  /// identifier.
  [[nodiscard]] virtual std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const = 0;

  /// Query pattern variables used in while statements.
  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryPatternVariablesFromWhile(int statement_number) const = 0;

  /// Query all if statements that has any patterns.
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllIfPattern()
      const = 0;

  /// Query all if patterns that uses a variable that matches a given
  /// identifier.
  [[nodiscard]] virtual std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const = 0;

  /// Query pattern variables used in if statements.
  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryPatternVariablesFromIf(int statement_number) const = 0;

  /// Query VarName, VarName, ProcName from given Print, Read, Call statement
  /// number respectively
  [[nodiscard]] virtual std::string QueryWithAttributeFromStatement(
      EntityType type, int statement_number) const = 0;

  /// Query entities that matches attribute identifier
  /// Treats x.procName = "name" &  with "name" = x.procName the same
  [[nodiscard]] virtual std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, std::string identifier) const = 0;

  /// Query entities that matches attribute number value or stmt#
  /// Treats x.value = 1 &  with 2 = x.stmt# the same
  [[nodiscard]] virtual std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, int number) const = 0;

  /// Checks with the pkb to see if the given statement number is a read, print,
  /// if, while, or assign statement
  [[nodiscard]] virtual bool CheckValidAffectsStmtNo(int stmt_no) const = 0;
};

#endif  // SPA_QUERYABLE_PKB_H
