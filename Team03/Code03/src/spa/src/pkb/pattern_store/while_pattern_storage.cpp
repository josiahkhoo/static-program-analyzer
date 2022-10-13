#include "while_pattern_storage.h"

/// Add While Pattern
/// \param abstraction
void WhilePatternStorage::AddWhilePattern(WhilePatternAbstraction abstraction) {
  int if_stmt_num = abstraction.GetLeftHandSide().GetStatementNumber();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!while_stmt_to_vars_patterns_map_
           .emplace(if_stmt_num, std::unordered_set<std::string>{var_name})
           .second) {
    while_stmt_to_vars_patterns_map_.at(if_stmt_num).emplace(var_name);
  }
  if (!var_to_while_stmts_patterns_map_
           .emplace(var_name, std::unordered_set<int>{if_stmt_num})
           .second) {
    var_to_while_stmts_patterns_map_.at(var_name).emplace(if_stmt_num);
  }
}

/// GetAllWhilePattern
/// \return Gets all While Statements that use a variable in conditional
/// container
std::unordered_set<std::string> WhilePatternStorage::GetAllWhilePattern()
    const {
  std::unordered_set<std::string> res;
  if (!while_stmt_to_vars_patterns_map_.empty()) {
    for (auto stmt : while_stmt_to_vars_patterns_map_) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

/// GetWhilePattern
/// \param var_ident
/// \return Get all While Statements that use var_ident in conditional container
std::unordered_set<std::string> WhilePatternStorage::GetWhilePattern(
    std::string var_ident) const {
  std::unordered_set<std::string> res;
  if (var_to_while_stmts_patterns_map_.find(var_ident) !=
      var_to_while_stmts_patterns_map_.end()) {
    for (auto stmt : var_to_while_stmts_patterns_map_.at(var_ident)) {
      res.emplace(std::to_string(stmt));
    }
  }
  return res;
}

/// GetPatternVariablesFromWhile
/// \param statement_number
/// \return Get all variables used in conditional container of given While
/// Statement
std::unordered_set<std::string>
WhilePatternStorage::GetPatternVariablesFromWhile(int statement_number) const {
  std::unordered_set<std::string> res;
  if (while_stmt_to_vars_patterns_map_.find(statement_number) !=
      while_stmt_to_vars_patterns_map_.end()) {
    for (auto var : while_stmt_to_vars_patterns_map_.at(statement_number)) {
      res.emplace(var);
    }
  }
  return res;
}
