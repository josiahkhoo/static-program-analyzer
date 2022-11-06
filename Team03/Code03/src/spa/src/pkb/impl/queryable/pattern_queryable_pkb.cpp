#include "pattern_queryable_pkb.h"

PatternQueryablePkb::PatternQueryablePkb(PatternManager& pattern_manager_)
    : assign_pattern_queryable_(pattern_manager_),
      while_pattern_queryable_(pattern_manager_),
      if_pattern_queryable_(pattern_manager_) {}

/// Get AssignPatternQueryable
/// \return AssignPatternQueryable
AssignPatternQueryable& PatternQueryablePkb::GetAssignPatternQueryable() {
  return assign_pattern_queryable_;
}

/// Get WhilePatternQueryable
/// \return WhilePatternQueryable
WhilePatternQueryable& PatternQueryablePkb::GetWhilePatternQueryable() {
  return while_pattern_queryable_;
}

/// Get IfPatternQueryable
/// \return IfPatternQueryable
IfPatternQueryable& PatternQueryablePkb::GetIfPatternQueryable() {
  return if_pattern_queryable_;
}
