//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_QUERYABLE_PKB_IMPL_H
#define SPA_QUERYABLE_PKB_IMPL_H

#include "pkb/impl/queryable/pattern_queryable_pkb.h"
#include "pkb/impl/queryable/relationship_queryable_pkb.h"

class QueryablePkbImpl {
 public:
  QueryablePkbImpl(EntityManager &entity_manager_,
                   RelationshipManager &relationship_manager_,
                   PatternManager &pattern_manager_);

  [[nodiscard]] EntityQueryable &GetEntityQueryable();
  [[nodiscard]] RelationshipQueryablePkb &GetRelationshipQueryablePkb();
  [[nodiscard]] PatternQueryablePkb &GetPatternQueryablePkb();

 private:
  EntityQueryable entity_queryable_;
  RelationshipQueryablePkb relationship_queryable_pkb_;
  PatternQueryablePkb pattern_queryable_pkb_;
};

#endif  // SPA_QUERYABLE_PKB_IMPL_H
