//
// Created by kohha on 3/11/2022.
//

#ifndef SPA_ENTITY_STORABLE_PKB_H
#define SPA_ENTITY_STORABLE_PKB_H

#include "common/entity/entity.h"
#include "pkb/entity_store/entity_manager.h"
#include "pkb/pattern_store/pattern_manager.h"
#include "storable_pkb_strategy.h"

template <class T>
class EntityStorablePkb : StorablePkbStrategy<T> {
 public:
  void Store(std::vector<T> ts) override;
 private:
  EntityManager entity_manager_;
  PatternManager pattern_manager_;
};

#endif  // SPA_ENTITY_STORABLE_PKB_H
