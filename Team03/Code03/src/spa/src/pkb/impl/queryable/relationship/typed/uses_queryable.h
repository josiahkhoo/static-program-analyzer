//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_USES_QUERYABLE_H
#define SPA_USES_QUERYABLE_H

#include "typed_queryable.h"

class UsesQueryable : TypedQueryable {
 public:
  explicit UsesQueryable(RelationshipManager &relationship_manager_,
                         EntityQueryable &entity_queryable_);

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
};

#endif  // SPA_USES_QUERYABLE_H
