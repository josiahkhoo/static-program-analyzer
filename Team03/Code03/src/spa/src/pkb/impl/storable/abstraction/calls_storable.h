//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CALLS_STORABLE_H
#define SPA_CALLS_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class CallsStorable : RelationshipAbstractionStorable,
                      StorablePkb<CallsAbstraction> {
 public:
  explicit CallsStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<CallsAbstraction> abstractions) override;
};

#endif  // SPA_CALLS_STORABLE_H
