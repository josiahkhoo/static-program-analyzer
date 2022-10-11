#ifndef SPA_WHILE_PATTERN_STORAGE_H
#define SPA_WHILE_PATTERN_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/abstraction/while_pattern_abstraction.h"

class WhilePatternStorage {
 public:
  void AddWhilePattern(WhilePatternAbstraction abstraction);

  std::unordered_set<std::string> GetAllWhilePattern() const;

  std::unordered_set<std::string> GetWhilePattern(std::string var_ident) const;

  std::unordered_set<std::string> GetPatternVariablesFromWhile(
      int statement_number) const;

 private:
  std::unordered_map<int, std::unordered_set<std::string>>
      while_stmt_to_vars_patterns_map_;
  std::unordered_map<std::string, std::unordered_set<int>>
      var_to_while_stmts_patterns_map_;
};

#endif  // SPA_WHILE_PATTERN_STORAGE_H
