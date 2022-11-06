#ifndef SPA_PATTERN_ABSTRACTION_STORABLE_H
#define SPA_PATTERN_ABSTRACTION_STORABLE_H

#include "pkb/pattern_store/pattern_manager.h"

class PatternAbstractionStorable {
 protected:
  explicit PatternAbstractionStorable(PatternManager &pattern_manager_);
  PatternManager &pattern_manager_;
};

#endif  // SPA_PATTERN_ABSTRACTION_STORABLE_H
