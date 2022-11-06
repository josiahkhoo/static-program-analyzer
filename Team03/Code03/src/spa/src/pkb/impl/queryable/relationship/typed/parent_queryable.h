#ifndef SPA_PARENT_QUERYABLE_H
#define SPA_PARENT_QUERYABLE_H

#include "typed_queryable.h"

class ParentQueryable : TypedQueryable {
 public:
  explicit ParentQueryable(RelationshipManager &relationship_manager_,
                           EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const;

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const;
};

#endif  // SPA_PARENT_QUERYABLE_H
