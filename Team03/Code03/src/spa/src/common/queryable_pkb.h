#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/entity/entity_type.h"
#include "string"
#include "unordered_set"

class QueryablePkb {
 public:
  [[nodiscard]] virtual std::unordered_set<std::string> QueryAll(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollow(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollowBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollow(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowT(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowTBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllParent(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const = 0;

};

#endif  // SPA_QUERYABLE_PKB_H
