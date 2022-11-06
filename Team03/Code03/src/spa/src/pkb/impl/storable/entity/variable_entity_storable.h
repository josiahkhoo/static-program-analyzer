#ifndef SPA_VARIABLE_ENTITY_STORABLE_H
#define SPA_VARIABLE_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class VariableEntityStorable : EntityStorable, StorablePkb<VariableEntity> {
 public:
  explicit VariableEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<VariableEntity> ts) override;
};

#endif  // SPA_VARIABLE_ENTITY_STORABLE_H
