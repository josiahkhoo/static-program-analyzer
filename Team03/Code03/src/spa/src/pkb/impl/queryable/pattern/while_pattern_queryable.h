#ifndef SPA_WHILE_PATTERN_QUERYABLE_H
#define SPA_WHILE_PATTERN_QUERYABLE_H

#include "pkb/pattern_store/pattern_manager.h"

class WhilePatternQueryable {
 public:
  explicit WhilePatternQueryable(const PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllWhilePattern() const;

  [[nodiscard]] std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int statement_number) const;
  
 private:
  const PatternManager &pattern_manager_;
};

#endif  // SPA_WHILE_PATTERN_QUERYABLE_H
