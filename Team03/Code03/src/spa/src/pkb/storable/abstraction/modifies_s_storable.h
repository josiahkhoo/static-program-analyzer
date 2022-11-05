//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_MODIFIES_S_STORABLE_H
#define SPA_MODIFIES_S_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class ModifiesSStorable : RelationshipAbstractionStorable, StorablePkb<ModifiesSAbstraction> {
 public:
  ModifiesSStorable();
  void Store(std::vector<ModifiesSAbstraction> abstractions) override;
};

#endif  // SPA_MODIFIES_S_STORABLE_H
