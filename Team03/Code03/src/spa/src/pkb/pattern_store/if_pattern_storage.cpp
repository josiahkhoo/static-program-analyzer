#include "if_pattern_storage.h"

/// Add If Pattern
/// \param abstraction
void IfPatternStorage::AddIfPattern(IfPatternAbstraction abstraction) {
  int if_stmt_num = abstraction.GetLeftHandSide().GetStatementNumber();
  std::string var_name = abstraction.GetRightHandSide().GetName();

  if (!if_stmt_to_vars_patterns_map_
           .emplace(if_stmt_num, std::unordered_set<std::string>{var_name})
           .second) {
    if_stmt_to_vars_patterns_map_.at(if_stmt_num).emplace(var_name);
  }
  if (!var_to_if_stmts_patterns_map_
           .emplace(var_name, std::unordered_set<int>{if_stmt_num})
           .second) {
    var_to_if_stmts_patterns_map_.at(var_name).emplace(if_stmt_num);
  }
}

/// GetAllIfPattern
/// \return Gets all If Statements that use a variable in conditional container
std::unordered_set<std::string> IfPatternStorage::GetAllIfPattern() const {
  std::unordered_set<std::string> res;
  if (!if_stmt_to_vars_patterns_map_.empty()) {
    for (auto stmt : if_stmt_to_vars_patterns_map_) {
      res.emplace(std::to_string(stmt.first));
    }
  }
  return res;
}

/// GetIfPattern
/// \param var_ident
/// \return Get all If Statements that use var_ident in conditional container
std::unordered_set<std::string> IfPatternStorage::GetIfPattern(
    std::string var_ident) const {
  std::unordered_set<std::string> res;
  if (var_to_if_stmts_patterns_map_.find(var_ident) !=
      var_to_if_stmts_patterns_map_.end()) {
    for (auto stmt : var_to_if_stmts_patterns_map_.at(var_ident)) {
      res.emplace(std::to_string(stmt));
    }
  }
  return res;
}

/// GetPatternVariablesFromIf
/// \param statement_number
/// \return Get all variables used in conditional container of given If
/// Statement
std::unordered_set<std::string> IfPatternStorage::GetPatternVariablesFromIf(
    int statement_number) const {
  std::unordered_set<std::string> res;
  if (if_stmt_to_vars_patterns_map_.find(statement_number) !=
      if_stmt_to_vars_patterns_map_.end()) {
    for (auto var : if_stmt_to_vars_patterns_map_.at(statement_number)) {
      res.emplace(var);
    }
  }
  return res;
}
