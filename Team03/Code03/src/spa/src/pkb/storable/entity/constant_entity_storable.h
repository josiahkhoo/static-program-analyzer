//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CONSTANT_ENTITY_STORABLE_H
#define SPA_CONSTANT_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class ConstantEntityStorable : EntityStorable, StorablePkb<ConstantEntity> {
 public:
  ConstantEntityStorable();
  void Store(std::vector<ConstantEntity> ts) override;
};

#endif  // SPA_CONSTANT_ENTITY_STORABLE_H
