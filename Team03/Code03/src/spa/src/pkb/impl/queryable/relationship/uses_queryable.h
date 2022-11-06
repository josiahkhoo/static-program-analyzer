#ifndef SPA_USES_QUERYABLE_H
#define SPA_USES_QUERYABLE_H

#include "pkb/impl/queryable/queryable_utility.h"

class UsesQueryable {
 public:
  explicit UsesQueryable(const RelationshipManager &relationship_manager_,
                         const EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const;

 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_USES_QUERYABLE_H
