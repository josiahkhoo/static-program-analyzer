#ifndef SPA_WHILE_PATTERN_QUERYABLE_H
#define SPA_WHILE_PATTERN_QUERYABLE_H

#include "pattern_queryable.h"

class WhilePatternQueryable : PatternQueryable {
 public:
  explicit WhilePatternQueryable(PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllWhilePattern() const;

  [[nodiscard]] std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int statement_number) const;
};

#endif  // SPA_WHILE_PATTERN_QUERYABLE_H
