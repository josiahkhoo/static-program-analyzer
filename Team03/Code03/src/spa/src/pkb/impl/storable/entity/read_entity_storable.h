#ifndef SPA_READ_ENTITY_STORABLE_H
#define SPA_READ_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class ReadEntityStorable : EntityStorable, StorablePkb<ReadEntity> {
 public:
  explicit ReadEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<ReadEntity> ts) override;
};

#endif  // SPA_READ_ENTITY_STORABLE_H
