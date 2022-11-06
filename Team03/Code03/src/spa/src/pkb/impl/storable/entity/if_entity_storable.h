#ifndef SPA_IF_ENTITY_STORABLE_H
#define SPA_IF_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class IfEntityStorable : EntityStorable, StorablePkb<IfEntity> {
 public:
  explicit IfEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<IfEntity> ts) override;
};

#endif  // SPA_IF_ENTITY_STORABLE_H
