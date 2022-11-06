#ifndef SPA_MODIFIES_QUERYABLE_H
#define SPA_MODIFIES_QUERYABLE_H

#include "pkb/impl/queryable/queryable_utility.h"

class ModifiesQueryable {
 public:
  explicit ModifiesQueryable(const RelationshipManager &relationship_manager_,
                             const EntityQueryable &entity_queryable_);

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
  
 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_MODIFIES_QUERYABLE_H
