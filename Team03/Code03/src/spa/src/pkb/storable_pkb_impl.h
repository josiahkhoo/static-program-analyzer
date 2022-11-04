//
// Created by kohha on 3/11/2022.
//

#ifndef SPA_STORABLE_PKB_IMPL_H
#define SPA_STORABLE_PKB_IMPL_H

#include "common/storable_pkb.h"
#include "pkb/strategy/storable/abstraction_storable_pkb_strategy.h"
#include "pkb/strategy/storable/entity_storable_pkb_strategy.h"
#include "pkb/strategy/storable/storable_pkb_strategy.h"

template <class T, class U, class V>
class StorablePkbImpl : public StorablePkb<T> {
 public:
  void Store(std::vector<Entity> ts) override;
  void Store(std::vector<Abstraction<U, V>> ts) override;

 private:
  EntityStorablePkb<Entity> entity_storable_pkb_;
  AbstractionStorablePkb<Abstraction<U, V>> abstraction_storable_pkb_;
};

#endif  // SPA_STORABLE_PKB_IMPL_H
