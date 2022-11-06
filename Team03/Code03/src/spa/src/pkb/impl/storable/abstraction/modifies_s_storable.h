#ifndef SPA_MODIFIES_S_STORABLE_H
#define SPA_MODIFIES_S_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class ModifiesSStorable : RelationshipAbstractionStorable,
                          StorablePkb<ModifiesSAbstraction> {
 public:
  explicit ModifiesSStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<ModifiesSAbstraction> abstractions) override;
};

#endif  // SPA_MODIFIES_S_STORABLE_H
