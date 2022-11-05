//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_WHILE_PATTERN_STORABLE_H
#define SPA_WHILE_PATTERN_STORABLE_H

#include "common/storable_pkb.h"
#include "pattern_abstraction_storable.h"

class WhilePatternStorable : PatternAbstractionStorable, StorablePkb<WhilePatternAbstraction> {
 public:
  explicit WhilePatternStorable(PatternManager &pattern_manager_);
  void Store(std::vector<WhilePatternAbstraction> abstractions) override;
};

#endif  // SPA_WHILE_PATTERN_STORABLE_H
