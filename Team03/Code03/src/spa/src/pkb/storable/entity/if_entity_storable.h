//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_IF_ENTITY_STORABLE_H
#define SPA_IF_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class IfEntityStorable : EntityStorable, StorablePkb<IfEntity> {
 public:
  IfEntityStorable();
  void Store(std::vector<IfEntity> ts) override;
};

#endif  // SPA_IF_ENTITY_STORABLE_H
