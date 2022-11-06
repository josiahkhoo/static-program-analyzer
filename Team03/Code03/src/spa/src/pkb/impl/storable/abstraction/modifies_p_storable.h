//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_MODIFIES_P_STORABLE_H
#define SPA_MODIFIES_P_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class ModifiesPStorable : RelationshipAbstractionStorable,
                          StorablePkb<ModifiesPAbstraction> {
 public:
  explicit ModifiesPStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<ModifiesPAbstraction> abstractions) override;
};

#endif  // SPA_MODIFIES_P_STORABLE_H
