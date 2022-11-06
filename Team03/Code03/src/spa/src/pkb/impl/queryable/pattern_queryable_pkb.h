//
// Created by kohha on 6/11/2022.
//

#ifndef SPA_PATTERN_QUERYABLE_PKB_H
#define SPA_PATTERN_QUERYABLE_PKB_H

#include "pkb/impl/queryable/pattern/assign_pattern_queryable.h"
#include "pkb/impl/queryable/pattern/if_pattern_queryable.h"
#include "pkb/impl/queryable/pattern/while_pattern_queryable.h"

class PatternQueryablePkb {
 public:
  explicit PatternQueryablePkb(PatternManager& pattern_manager_);

  [[nodiscard]] AssignPatternQueryable& GetAssignPatternQueryable();

  [[nodiscard]] WhilePatternQueryable& GetWhilePatternQueryable();

  [[nodiscard]] IfPatternQueryable& GetIfPatternQueryable();

 private:
  AssignPatternQueryable assign_pattern_queryable_;
  WhilePatternQueryable while_pattern_queryable_;
  IfPatternQueryable if_pattern_queryable_;
};

#endif  // SPA_PATTERN_QUERYABLE_PKB_H
