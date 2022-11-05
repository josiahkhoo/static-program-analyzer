//
// Created by kohha on 5/11/2022.
//

#include "queryable_pkb_impl.h"

QueryablePkbImpl::QueryablePkbImpl(EntityManager& entity_manager_,
                                   RelationshipManager& relationship_manager)
    : entity_queryable(entity_manager_),
      typed_queryable_pkb_(relationship_manager, entity_queryable) {}

TypedQueryablePkb& QueryablePkbImpl::GetTypedQueryablePkb() {
  return typed_queryable_pkb_;
}
