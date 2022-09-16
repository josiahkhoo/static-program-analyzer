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

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllPattern(
      Expression exp) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryPattern(
      EntityType type, Expression exp) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryPattern(
      std::string lhs, Expression exp) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesP() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesP(
      std::string procedure_name) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesPBy() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesPBy(
      std::string variable_name) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesS() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesS(
      int statement_number) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesSBy() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetUsesSBy(
      std::string variable_name) const = 0;
};

#endif  // SPA_QUERYABLE_PKB_H
