//
// Created by kohha on 6/11/2022.
//

#ifndef SPA_PATTERN_QUERYABLE_H
#define SPA_PATTERN_QUERYABLE_H

#include "pkb/pattern_store/pattern_manager.h"

class PatternQueryable {
 protected:
  explicit PatternQueryable(PatternManager &pattern_manager_);
  PatternManager &pattern_manager_;
};

#endif  // SPA_PATTERN_QUERYABLE_H
