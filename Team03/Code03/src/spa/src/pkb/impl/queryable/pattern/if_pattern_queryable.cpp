//
// Created by kohha on 6/11/2022.
//

#include "if_pattern_queryable.h"

IfPatternQueryable::IfPatternQueryable(PatternManager& pattern_manager_)
    : PatternQueryable(pattern_manager_) {}

/// QueryAllIfPattern
/// \return Get all If Statements that use a variable in conditional container
std::unordered_set<std::string> IfPatternQueryable::QueryAllIfPattern() const {
  return pattern_manager_.GetAllIfPattern();
}

/// QueryIfPattern
/// \param ident
/// \return Get all If Statements that use variable ident in conditional
/// container
std::unordered_set<std::string> IfPatternQueryable::QueryIfPattern(
    std::string ident) const {
  return pattern_manager_.GetIfPattern(ident);
}

/// QueryPatternVariablesFromIf
/// \param statement_number
/// \return Get all variables used in conditional container of given If
/// Statement
std::unordered_set<std::string> IfPatternQueryable::QueryPatternVariablesFromIf(
    int statement_number) const {
  return pattern_manager_.GetPatternVariablesFromIf(statement_number);
}
