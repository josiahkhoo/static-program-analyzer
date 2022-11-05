//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_USES_S_STORABLE_H
#define SPA_USES_S_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class UsesSStorable : RelationshipAbstractionStorable, StorablePkb<UsesSAbstraction> {
 public:
  UsesSStorable();
  void Store(std::vector<UsesSAbstraction> abstractions) override;
};

#endif  // SPA_USES_S_STORABLE_H
