//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_IF_PATTERN_STORABLE_H
#define SPA_IF_PATTERN_STORABLE_H

#include "common/storable_pkb.h"
#include "pattern_abstraction_storable.h"

class IfPatternStorable : PatternAbstractionStorable, StorablePkb<IfPatternAbstraction> {
 public:
  explicit IfPatternStorable(PatternManager &pattern_manager_);
  void Store(std::vector<IfPatternAbstraction> abstractions) override;
};

#endif  // SPA_IF_PATTERN_STORABLE_H
