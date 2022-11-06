#ifndef SPA_MODIFIES_QUERYABLE_H
#define SPA_MODIFIES_QUERYABLE_H

#include "typed_queryable.h"

class ModifiesQueryable : TypedQueryable {
 public:
  explicit ModifiesQueryable(RelationshipManager &relationship_manager_,
                             EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int statement_number) const;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string identifier) const;

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier) const;
};

#endif  // SPA_MODIFIES_QUERYABLE_H
