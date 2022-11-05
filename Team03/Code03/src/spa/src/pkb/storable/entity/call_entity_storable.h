//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CALL_ENTITY_STORABLE_H
#define SPA_CALL_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class CallEntityStorable : EntityStorable, StorablePkb<CallEntity> {
 public:
  CallEntityStorable();
  void Store(std::vector<CallEntity> ts) override;
};

#endif  // SPA_CALL_ENTITY_STORABLE_H
