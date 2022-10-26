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
    std::string pattern, bool front_wildcard, bool back_wildcard) const {
  std::string::size_type pattern_start_pos = 0;
  std::string::size_type pattern_end_pos = 0;
  for (int i = 0; i < (int)pattern.size(); i++) {
    if (pattern[i] == '(') {
      pattern_start_pos++;
    } else {
      break;
    }
  }
  for (int i = pattern.size() - 1; i >= 0; i--) {
    if (pattern[i] == ')') {
      pattern_end_pos++;
    } else {
      break;
    }
  }

  std::unordered_set<std::string> res;

  if (!front_wildcard && !back_wildcard) {
    for (auto i : stmt_to_exp_map_) {
      if (i.second.compare(pattern) == 0) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else if (front_wildcard && back_wildcard) {
    for (auto i : stmt_to_exp_map_) {
      if (i.second.find(pattern) != std::string::npos) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else {
    throw std::invalid_argument("Missing wildcard booleans");
  }
  return res;
}

std::unordered_set<std::string> AssignPatternStorage::GetPattern(
    std::string lhs, std::string pattern, bool front_wildcard,
    bool back_wildcard) const {
  std::string::size_type pattern_start_pos = 0;
  std::string::size_type pattern_end_pos = 0;
  for (int i = 0; i < (int)pattern.size(); i++) {
    if (pattern[i] == '(') {
      pattern_start_pos++;
    } else {
      break;
    }
  }
  for (int i = pattern.size() - 1; i >= 0; i--) {
    if (pattern[i] == ')') {
      pattern_end_pos++;
    } else {
      break;
    }
  }

  std::unordered_set<std::string> res;
  std::unordered_set<int> lhs_stmts = {};
  if (var_to_stmt_map_.find(lhs) != var_to_stmt_map_.end()) {
    lhs_stmts = var_to_stmt_map_.find(lhs)->second;
  }
  if (!front_wildcard && !back_wildcard) {
    std::unordered_set<int> rhs_stmts = {};
    if (exp_to_stmt_map_.find(pattern) != exp_to_stmt_map_.end()) {
      rhs_stmts = exp_to_stmt_map_.find(pattern)->second;
    }
    for (auto i : lhs_stmts) {
      if (rhs_stmts.find(i) != rhs_stmts.end()) {
        res.emplace(std::to_string(i));
      }
    }
  } else if (front_wildcard && back_wildcard) {
    std::unordered_set<int> stmts = {};
    if (!exp_to_stmt_map_.empty()) {
      for (auto i : exp_to_stmt_map_) {
        if (i.first.find(pattern) != std::string::npos) {
          stmts.merge(i.second);
        }
      }
    }
    for (auto i : lhs_stmts) {
      if (stmts.find(i) != stmts.end()) {
        res.emplace(std::to_string(i));
      }
    }
  } else {
    throw std::invalid_argument("Missing wildcard booleans");
  }
  return res;
}
