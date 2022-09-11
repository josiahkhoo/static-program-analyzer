#ifndef SPA_PATTERN_MANAGER_H
#define SPA_PATTERN_MANAGER_H

#include <string>
#include <vector>

#include "assign_pattern_storage.h"
#include "common/entity/assign_entity.h"
#include "common/reference/expression.h"
#include "query_pattern_processor.h"

class PatternManager {
 public:
  PatternManager();

  void AddAssignPattern(AssignEntity statement);

  std::unordered_set<std::string> GetAllPattern(Expression exp) const;

  std::unordered_set<std::string> GetPattern(std::string lhs,
                                             Expression exp) const;

  void Clear();

 private:
  static AssignPatternStorage assign_pattern_storage_;
  static QueryPatternProcessor query_pattern_processor_;
};

#endif  // SPA_PATTERN_MANAGER_H
