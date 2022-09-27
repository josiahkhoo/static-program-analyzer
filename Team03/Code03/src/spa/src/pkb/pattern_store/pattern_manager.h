#ifndef SPA_PATTERN_MANAGER_H
#define SPA_PATTERN_MANAGER_H

#include <string>
#include <vector>

#include "assign_pattern_storage.h"
#include "common/abstraction/if_pattern_abstraction.h"
#include "common/abstraction/while_pattern_abstraction.h"
#include "common/entity/assign_entity.h"
#include "common/reference/expression.h"
#include "if_pattern_storage.h"
#include "query_pattern_processor.h"
#include "while_pattern_storage.h"

class PatternManager {
 public:
  void AddAssignPattern(AssignEntity statement);

  void AddIfPattern(IfPatternAbstraction abstraction);

  void AddWhilePattern(WhilePatternAbstraction abstraction);

  std::unordered_set<std::string> GetAllPattern(Expression exp) const;

  std::unordered_set<std::string> GetPattern(std::string lhs,
                                             Expression exp) const;

  std::unordered_set<std::string> GetAllIfPattern() const;

  std::unordered_set<std::string> GetIfPattern(std::string var_ident) const;

  std::unordered_set<std::string> GetPatternVariablesFromIf(
      int statement_number) const;

  std::unordered_set<std::string> GetAllWhilePattern() const;

  std::unordered_set<std::string> GetWhilePattern(std::string var_ident) const;

  std::unordered_set<std::string> GetPatternVariablesFromWhile(
      int statement_number) const;

  void Clear();

 private:
  AssignPatternStorage assign_pattern_storage_;
  IfPatternStorage if_pattern_storage_;
  WhilePatternStorage while_pattern_storage_;
  QueryPatternProcessor query_pattern_processor_;
};

#endif  // SPA_PATTERN_MANAGER_H
