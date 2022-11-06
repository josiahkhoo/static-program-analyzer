#ifndef SPA_PARENT_STORABLE_H
#define SPA_PARENT_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class ParentStorable : RelationshipAbstractionStorable,
                       StorablePkb<ParentAbstraction> {
 public:
  explicit ParentStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<ParentAbstraction> abstractions) override;
};

#endif  // SPA_PARENT_STORABLE_H
