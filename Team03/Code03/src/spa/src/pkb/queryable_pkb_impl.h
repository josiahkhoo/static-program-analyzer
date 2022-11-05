//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_QUERYABLE_PKB_IMPL_H
#define SPA_QUERYABLE_PKB_IMPL_H

#include "common/storable_pkb.h"
#include "pkb/storable/abstraction_storable_pkb.h"
#include "pkb/storable/entity_storable_pkb.h"
#include "pkb/queryable/typed_queryable_pkb.h"

class QueryablePkbImpl {
 public:
  QueryablePkbImpl(EntityManager &entity_manager_,
                  RelationshipManager &relationship_manager);

  [[nodiscard]] TypedQueryablePkb& GetTypedQueryablePkb();
//  [[nodiscard]] AbstractionStorablePkb& GetAbstractionStorablePkb();
 private:
  EntityQueryable entity_queryable;
  TypedQueryablePkb typed_queryable_pkb_;
//  AbstractionStorablePkb abstraction_storable_pkb_;
};

#endif  // SPA_QUERYABLE_PKB_IMPL_H
