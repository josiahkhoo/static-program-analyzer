#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/entity/entity_type.h"
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

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const = 0;
};

#endif  // SPA_QUERYABLE_PKB_H
