//
// Created by kohha on 4/11/2022.
//

#include "common/entity/entity.h"
#include "pkb/pattern_store/pattern_manager.h"
#include "pkb/relationship_store/relationship_manager.h"
#include "storable_pkb_strategy.h"

#ifndef SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
#define SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H

template <class T>
class AbstractionStorablePkb : StorablePkbStrategy<T> {
 public:
  void Store(std::vector<T> ts) override;

 private:
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
};

#endif  // SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
