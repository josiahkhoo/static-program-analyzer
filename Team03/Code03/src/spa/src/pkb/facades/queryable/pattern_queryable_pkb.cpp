#include "pattern_queryable_pkb.h"

PatternQueryablePkb::PatternQueryablePkb(const PatternManager& pattern_manager_)
    : assign_pattern_queryable_(pattern_manager_),
      while_pattern_queryable_(pattern_manager_),
      if_pattern_queryable_(pattern_manager_) {}

/// Get AssignPatternQueryable
/// \return AssignPatternQueryable
const AssignPatternQueryable& PatternQueryablePkb::GetAssignPatternQueryable()
    const {
  return assign_pattern_queryable_;
}

/// Get WhilePatternQueryable
/// \return WhilePatternQueryable
const WhilePatternQueryable& PatternQueryablePkb::GetWhilePatternQueryable()
    const {
  return while_pattern_queryable_;
}

/// Get IfPatternQueryable
/// \return IfPatternQueryable
const IfPatternQueryable& PatternQueryablePkb::GetIfPatternQueryable() const {
  return if_pattern_queryable_;
}
