#ifndef SPA_PARENT_QUERYABLE_H
#define SPA_PARENT_QUERYABLE_H

#include "pkb/impl/queryable/queryable_utility.h"

class ParentQueryable {
 public:
  explicit ParentQueryable(const RelationshipManager &relationship_manager_,
                           const EntityQueryable &entity_queryable_);

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

 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_PARENT_QUERYABLE_H
