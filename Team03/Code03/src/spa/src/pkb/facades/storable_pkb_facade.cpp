#include "storable_pkb_facade.h"

StorablePkbFacade::StorablePkbFacade(EntityManager &entity_manager_,
                                     RelationshipManager &relationship_manager,
                                     PatternManager &pattern_manager_)
    : entity_storable_pkb_(
          EntityStorablePkb(entity_manager_, pattern_manager_)),
      abstraction_storable_pkb_(
          AbstractionStorablePkb(relationship_manager, pattern_manager_)) {}

EntityStorablePkb &StorablePkbFacade::GetEntityStorablePkb() {
  return entity_storable_pkb_;
}

AbstractionStorablePkb &StorablePkbFacade::GetAbstractionStorablePkb() {
  return abstraction_storable_pkb_;
}
