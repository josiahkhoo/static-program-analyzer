#ifndef SPA_CONSTANT_ENTITY_STORABLE_H
#define SPA_CONSTANT_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class ConstantEntityStorable : EntityStorable, StorablePkb<ConstantEntity> {
 public:
  explicit ConstantEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<ConstantEntity> ts) override;
};

#endif  // SPA_CONSTANT_ENTITY_STORABLE_H
