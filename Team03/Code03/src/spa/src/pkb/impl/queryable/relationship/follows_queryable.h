#ifndef SPA_FOLLOWS_QUERYABLE_H
#define SPA_FOLLOWS_QUERYABLE_H

#include "common/entity/entity_type.h"
#include "pkb/impl/queryable/queryable_utility.h"

class FollowsQueryable {
 public:
  explicit FollowsQueryable(const RelationshipManager &relationship_manager_,
                            const EntityQueryable &entity_queryable_);

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

 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_FOLLOWS_QUERYABLE_H
