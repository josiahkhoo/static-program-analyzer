#ifndef SPA_ASSIGN_PATTERN_QUERYABLE_H
#define SPA_ASSIGN_PATTERN_QUERYABLE_H

#include "pattern_queryable.h"

class AssignPatternQueryable : PatternQueryable {
 public:
  explicit AssignPatternQueryable(PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int statement_number) const;
};

#endif  // SPA_ASSIGN_PATTERN_QUERYABLE_H
