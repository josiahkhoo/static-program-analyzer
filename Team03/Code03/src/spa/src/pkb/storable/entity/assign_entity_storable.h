//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_ASSIGN_ENTITY_STORABLE_H
#define SPA_ASSIGN_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"
#include "pkb/pattern_store/pattern_manager.h"

class AssignEntityStorable : EntityStorable, StorablePkb<AssignEntity> {
 public:
  AssignEntityStorable();
  void Store(std::vector<AssignEntity> ts) override;
 private:
  PatternManager pattern_manager_;
};

#endif  // SPA_ASSIGN_ENTITY_STORABLE_H
