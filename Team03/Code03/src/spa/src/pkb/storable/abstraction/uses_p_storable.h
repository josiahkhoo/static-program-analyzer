//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_USES_P_STORABLE_H
#define SPA_USES_P_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class UsesPStorable : RelationshipAbstractionStorable, StorablePkb<UsesPAbstraction> {
 public:
  explicit UsesPStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<UsesPAbstraction> abstractions) override;
};

#endif  // SPA_USES_P_STORABLE_H
