#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/entity/entity_type.h"
#include "common/reference/expression.h"
#include "string"
#include "unordered_set"

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

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllUsesSBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllUsesRelations()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllUsesPBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string>
  QueryAllModifiesRelations() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesS(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesP(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCalls(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCallsBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllCallsRelations()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCalls(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsBy(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsT(
      std::string identifier, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier, EntityType type) const = 0;

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
};

#endif  // SPA_QUERYABLE_PKB_H
