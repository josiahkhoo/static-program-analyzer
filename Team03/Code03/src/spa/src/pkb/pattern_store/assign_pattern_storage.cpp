#include "assign_pattern_storage.h"

#include <stdexcept>

void AssignPatternStorage::AddAssignPattern(int statement_number,
                                            std::string lhs, std::string rhs) {
  stmt_to_var_map_.emplace(statement_number, lhs);
  if (!var_to_stmt_map_.emplace(lhs, std::unordered_set<int>{statement_number})
           .second) {
    var_to_stmt_map_.at(lhs).emplace(statement_number);
  }
  stmt_to_exp_map_.emplace(statement_number, rhs);
  if (!exp_to_stmt_map_.emplace(rhs, std::unordered_set<int>{statement_number})
           .second) {
    exp_to_stmt_map_.at(rhs).emplace(statement_number);
  }
}

std::unordered_set<std::string> AssignPatternStorage::GetAllPattern(
    std::string pattern, bool has_wildcard) const {
  std::unordered_set<std::string> res;
  if (!has_wildcard) {
    for (auto i : stmt_to_exp_map_) {
      if (i.second.compare(pattern) == 0) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else {
    for (auto i : stmt_to_exp_map_) {
      if (i.second.find(pattern) != std::string::npos) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  return res;
}

std::unordered_set<std::string> AssignPatternStorage::GetPattern(
    std::string lhs, std::string pattern, bool has_wildcard) const {
  std::unordered_set<std::string> res;
  std::unordered_set<int> lhs_stmts = {};
  if (var_to_stmt_map_.find(lhs) != var_to_stmt_map_.end()) {
    lhs_stmts = var_to_stmt_map_.find(lhs)->second;
  }
  if (!has_wildcard) {
    for (auto i : lhs_stmts) {
      auto entry = stmt_to_exp_map_.find(i);
      if (entry->second == pattern) res.emplace((std::to_string(i)));
    }
  } else {
    for (auto i : lhs_stmts) {
      auto entry = stmt_to_exp_map_.find(i);
      if (entry->second.find(pattern) != std::string::npos)
        res.emplace((std::to_string(i)));
    }
  }
  return res;
}
