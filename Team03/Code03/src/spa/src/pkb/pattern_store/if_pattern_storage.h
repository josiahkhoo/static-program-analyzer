#ifndef SPA_IF_PATTERN_STORAGE_H
#define SPA_IF_PATTERN_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/abstraction/if_pattern_abstraction.h"

class IfPatternStorage {
 public:
  void AddIfPattern(IfPatternAbstraction abstraction);

  std::unordered_set<std::string> GetAllIfPattern() const;

  std::unordered_set<std::string> GetIfPattern(std::string var_ident) const;

  std::unordered_set<std::string> GetPatternVariablesFromIf(
      int statement_number) const;

 private:
  std::unordered_map<int, std::unordered_set<std::string>>
      if_stmt_to_vars_patterns_map_;
  std::unordered_map<std::string, std::unordered_set<int>>
      var_to_if_stmts_patterns_map_;
};

#endif  // SPA_IF_PATTERN_STORAGE_H
