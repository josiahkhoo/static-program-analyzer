#include "while_pattern_queryable.h"

WhilePatternQueryable::WhilePatternQueryable(PatternManager& pattern_manager_)
    : PatternQueryable(pattern_manager_) {}

/// QueryAllWhilePattern
/// \return Get all While Statements that use a variable in conditional
/// container
std::unordered_set<std::string> WhilePatternQueryable::QueryAllWhilePattern()
    const {
  return pattern_manager_.GetAllWhilePattern();
}

/// QueryWhilePattern
/// \param ident
/// \return Get all While Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> WhilePatternQueryable::QueryWhilePattern(
    std::string ident) const {
  return pattern_manager_.GetWhilePattern(ident);
}

/// QueryPatternVariablesFromWhile
/// \param statement_number
/// \return Get all variables used in conditional container of given While
/// Statement
std::unordered_set<std::string>
WhilePatternQueryable::QueryPatternVariablesFromWhile(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromWhile(statement_number);
}
