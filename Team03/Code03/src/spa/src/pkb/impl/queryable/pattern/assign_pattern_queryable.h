#ifndef SPA_ASSIGN_PATTERN_QUERYABLE_H
#define SPA_ASSIGN_PATTERN_QUERYABLE_H

#include "pkb/pattern_store/pattern_manager.h"

class AssignPatternQueryable {
 public:
  explicit AssignPatternQueryable(const PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int statement_number) const;
  
 private:
  const PatternManager &pattern_manager_;
};

#endif  // SPA_ASSIGN_PATTERN_QUERYABLE_H
