//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CALLS_T_STORABLE_H
#define SPA_CALLS_T_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class CallsTStorable : RelationshipAbstractionStorable,
                       StorablePkb<CallsTAbstraction> {
 public:
  explicit CallsTStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<CallsTAbstraction> abstractions) override;
};

#endif  // SPA_CALLS_T_STORABLE_H
