#ifndef SPA_PRINT_ENTITY_STORABLE_H
#define SPA_PRINT_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class PrintEntityStorable : EntityStorable, StorablePkb<PrintEntity> {
 public:
  explicit PrintEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<PrintEntity> ts) override;
};

#endif  // SPA_PRINT_ENTITY_STORABLE_H
