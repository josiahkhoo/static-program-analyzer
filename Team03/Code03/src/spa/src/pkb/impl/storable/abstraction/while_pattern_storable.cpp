#include "while_pattern_storable.h"

WhilePatternStorable::WhilePatternStorable(PatternManager& pattern_manager_)
    : PatternAbstractionStorable(pattern_manager_) {}

/// Store While Pattern Abstractions
/// \param abstractions List of abstractions
void WhilePatternStorable::Store(
    std::vector<WhilePatternAbstraction> abstractions) {
  for (const WhilePatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddWhilePattern(abstraction);
  }
}
