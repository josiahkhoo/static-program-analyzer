//
// Created by kohha on 5/11/2022.
//

#include "if_pattern_storable.h"

IfPatternStorable::IfPatternStorable(PatternManager& pattern_manager_)
    : PatternAbstractionStorable(pattern_manager_) {}

/// Store If Pattern Abstractions
/// \param abstractions List of abstractions
void IfPatternStorable::Store(std::vector<IfPatternAbstraction> abstractions) {
  for (const IfPatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddIfPattern(abstraction);
  }
}
