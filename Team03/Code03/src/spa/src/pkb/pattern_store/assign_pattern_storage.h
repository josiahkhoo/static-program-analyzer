#ifndef SPA_ASSIGN_PATTERN_STORAGE_H
#define SPA_ASSIGN_PATTERN_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/assign_entity.h"
#include "common/reference/expression.h"

class AssignPatternStorage {
 public:
  void AddAssignPattern(int statement_number, std::string lhs, std::string rhs);

  std::unordered_set<std::string> GetAllPattern(std::string pattern,
                                                bool has_wildcard) const;

  std::unordered_set<std::string> GetPattern(std::string lhs,
                                             std::string pattern,
                                             bool has_wildcard) const;

 private:
  std::unordered_map<int, std::string> stmt_to_var_map_;
  std::unordered_map<std::string, std::unordered_set<int>> var_to_stmt_map_;
  std::unordered_map<int, std::string> stmt_to_exp_map_;
  std::unordered_map<std::string, std::unordered_set<int>> exp_to_stmt_map_;
};

#endif  // SPA_ASSIGN_PATTERN_STORAGE_H
