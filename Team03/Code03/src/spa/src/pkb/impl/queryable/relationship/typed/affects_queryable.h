#ifndef SPA_AFFECTS_QUERYABLE_H
#define SPA_AFFECTS_QUERYABLE_H

#include "typed_queryable.h"

class AffectsQueryable : TypedQueryable {
 public:
  explicit AffectsQueryable(RelationshipManager &relationship_manager_,
                            EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffects();

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffectsBy();

  [[nodiscard]] std::unordered_set<std::string> QueryAffects(
      int statement_number);

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsBy(
      int statement_number);

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsT(
      int statement_number);

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number);
};

#endif  // SPA_AFFECTS_QUERYABLE_H
