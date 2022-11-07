#ifndef SPA_PATTERN_QUERYABLE_PKB_H
#define SPA_PATTERN_QUERYABLE_PKB_H

#include "pkb/facades/queryable/pattern/assign_pattern_queryable.h"
#include "pkb/facades/queryable/pattern/if_pattern_queryable.h"
#include "pkb/facades/queryable/pattern/while_pattern_queryable.h"

class PatternQueryablePkb {
 public:
  explicit PatternQueryablePkb(const PatternManager& pattern_manager_);

  [[nodiscard]] const AssignPatternQueryable& GetAssignPatternQueryable() const;

  [[nodiscard]] const WhilePatternQueryable& GetWhilePatternQueryable() const;

  [[nodiscard]] const IfPatternQueryable& GetIfPatternQueryable() const;

 private:
  const AssignPatternQueryable assign_pattern_queryable_;
  const WhilePatternQueryable while_pattern_queryable_;
  const IfPatternQueryable if_pattern_queryable_;
};

#endif  // SPA_PATTERN_QUERYABLE_PKB_H
