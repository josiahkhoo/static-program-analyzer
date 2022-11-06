//
// Created by kohha on 6/11/2022.
//

#include "assign_pattern_queryable.h"

AssignPatternQueryable::AssignPatternQueryable(PatternManager& pattern_manager_)
    : PatternQueryable(pattern_manager_) {}

std::unordered_set<std::string> AssignPatternQueryable::QueryAllAssignPattern(
    Expression exp) const {
  return pattern_manager_.GetAllPattern(exp);
}

std::unordered_set<std::string> AssignPatternQueryable::QueryAssignPattern(
    std::string lhs, Expression exp) const {
  return pattern_manager_.GetPattern(lhs, exp);
}

std::unordered_set<std::string>
AssignPatternQueryable::QueryPatternVariablesFromAssign(int) const {
  return {};
}
