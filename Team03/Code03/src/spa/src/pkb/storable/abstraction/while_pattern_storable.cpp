//
// Created by kohha on 5/11/2022.
//

#include "while_pattern_storable.h"

WhilePatternStorable::WhilePatternStorable() = default;

/// Store While Pattern Abstractions
/// \param abstractions List of abstractions
void WhilePatternStorable::Store(std::vector<WhilePatternAbstraction> abstractions) {
  for (const WhilePatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddWhilePattern(abstraction);
  }
}
