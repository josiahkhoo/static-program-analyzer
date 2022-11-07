#ifndef SPA_QUERYABLE_PKB_IMPL_H
#define SPA_QUERYABLE_PKB_IMPL_H

#include "pkb/facades/queryable/pattern_queryable_pkb.h"
#include "pkb/facades/queryable/relationship_queryable_pkb.h"

class QueryablePkbFacade {
 public:
  QueryablePkbFacade(const EntityManager &entity_manager_,
                     const RelationshipManager &relationship_manager_,
                     const PatternManager &pattern_manager_);

  [[nodiscard]] const EntityQueryable &GetEntityQueryable() const;
  [[nodiscard]] const RelationshipQueryablePkb &GetRelationshipQueryablePkb()
      const;
  [[nodiscard]] const PatternQueryablePkb &GetPatternQueryablePkb() const;

 private:
  const EntityQueryable entity_queryable_;
  const RelationshipQueryablePkb relationship_queryable_pkb_;
  const PatternQueryablePkb pattern_queryable_pkb_;
};

#endif  // SPA_QUERYABLE_PKB_IMPL_H
