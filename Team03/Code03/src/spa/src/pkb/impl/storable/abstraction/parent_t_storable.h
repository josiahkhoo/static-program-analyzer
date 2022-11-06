//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_PARENT_T_STORABLE_H
#define SPA_PARENT_T_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class ParentTStorable : RelationshipAbstractionStorable,
                        StorablePkb<ParentTAbstraction> {
 public:
  explicit ParentTStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<ParentTAbstraction> abstractions) override;
};

#endif  // SPA_PARENT_T_STORABLE_H
