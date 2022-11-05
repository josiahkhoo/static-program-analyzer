//
// Created by kohha on 3/11/2022.
//

#include "storable_pkb_impl.h"

StorablePkbImpl::StorablePkbImpl(EntityManager &entity_manager_,
                                 RelationshipManager &relationship_manager,
                                 PatternManager &pattern_manager_)
    : entity_storable_pkb_(
          EntityStorablePkb(entity_manager_, pattern_manager_)),
      abstraction_storable_pkb_(
          AbstractionStorablePkb(relationship_manager, pattern_manager_)) {}

EntityStorablePkb& StorablePkbImpl::GetEntityStorablePkb() {
  return entity_storable_pkb_;
}

AbstractionStorablePkb& StorablePkbImpl::GetAbstractionStorablePkb() {
  return abstraction_storable_pkb_;
}
