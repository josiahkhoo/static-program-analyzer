//
// Created by kohha on 6/11/2022.
//

#ifndef SPA_IF_PATTERN_QUERYABLE_H
#define SPA_IF_PATTERN_QUERYABLE_H

#include "pattern_queryable.h"

class IfPatternQueryable : PatternQueryable {
 public:
  explicit IfPatternQueryable(PatternManager &pattern_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllIfPattern() const;

  [[nodiscard]] std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int statement_number) const;
};

#endif  // SPA_IF_PATTERN_QUERYABLE_H
