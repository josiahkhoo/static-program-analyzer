//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_WHILE_ENTITY_STORABLE_H
#define SPA_WHILE_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class WhileEntityStorable : EntityStorable, StorablePkb<WhileEntity> {
 public:
  explicit WhileEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<WhileEntity> ts) override;
};

#endif  // SPA_WHILE_ENTITY_STORABLE_H
