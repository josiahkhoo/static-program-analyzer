//
// Created by kohha on 3/11/2022.
//

#ifndef SPA_STORABLE_PKB_IMPL_H
#define SPA_STORABLE_PKB_IMPL_H

#include "common/storable_pkb.h"
#include "pkb/storable/abstraction_storable_pkb.h"
#include "pkb/storable/entity_storable_pkb.h"

class StorablePkbImpl {
 public:
  StorablePkbImpl(EntityManager &entity_manager_,
                  RelationshipManager &relationship_manager,
                  PatternManager &pattern_manager_);

  [[nodiscard]] EntityStorablePkb& GetEntityStorablePkb();
  [[nodiscard]] AbstractionStorablePkb& GetAbstractionStorablePkb();


 private:
  EntityStorablePkb entity_storable_pkb_;
  AbstractionStorablePkb abstraction_storable_pkb_;
};

#endif  // SPA_STORABLE_PKB_IMPL_H
