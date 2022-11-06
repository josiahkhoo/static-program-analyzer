//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_FOLLOWS_QUERYABLE_H
#define SPA_FOLLOWS_QUERYABLE_H

#include "common/entity/entity_type.h"
#include "typed_queryable.h"

class FollowsQueryable : TypedQueryable {
 public:
  explicit FollowsQueryable(RelationshipManager &relationship_manager_,
                            EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const;

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const;
};

#endif  // SPA_FOLLOWS_QUERYABLE_H
