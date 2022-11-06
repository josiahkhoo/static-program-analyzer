#ifndef SPA_AFFECTS_QUERYABLE_H
#define SPA_AFFECTS_QUERYABLE_H

#include "pkb/impl/queryable/queryable_utility.h"

class AffectsQueryable {
 public:
  explicit AffectsQueryable(const RelationshipManager &relationship_manager_,
                            const EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffects() const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffectsBy() const;

  [[nodiscard]] std::unordered_set<std::string> QueryAffects(
      int statement_number) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsBy(
      int statement_number) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsT(
      int statement_number) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number) const;

 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_AFFECTS_QUERYABLE_H
