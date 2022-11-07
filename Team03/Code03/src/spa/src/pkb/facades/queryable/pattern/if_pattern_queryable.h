#ifndef SPA_IF_PATTERN_QUERYABLE_H
#define SPA_IF_PATTERN_QUERYABLE_H

#include "pkb/pattern_store/pattern_manager.h"

class IfPatternQueryable {
 public:
  explicit IfPatternQueryable(const PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllIfPattern() const;

  [[nodiscard]] std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int statement_number) const;

 private:
  const PatternManager &pattern_manager_;
};

#endif  // SPA_IF_PATTERN_QUERYABLE_H
