#include "pattern_manager.h"

void PatternManager::AddAssignPattern(AssignEntity statement) {
  int statement_number = statement.GetStatementNumber();
  std::string lhs = statement.GetLeftHandSidePattern();
  std::string rhs = statement.GetRightHandSidePattern();
  assign_pattern_storage_.AddAssignPattern(statement_number, lhs, rhs);
}

void PatternManager::AddIfPattern(IfPatternAbstraction abstraction) {
  if_pattern_storage_.AddIfPattern(abstraction);
}

void PatternManager::AddWhilePattern(WhilePatternAbstraction abstraction) {
  while_pattern_storage_.AddWhilePattern(abstraction);
}

std::unordered_set<std::string> PatternManager::GetAllPattern(
    Expression exp) const {
  std::string pattern =
      query_pattern_processor_.ProcessAssignPattern(exp.to_match);
  return assign_pattern_storage_.GetAllPattern(pattern, exp.has_wildcard);
}

std::unordered_set<std::string> PatternManager::GetPattern(
    std::string lhs, Expression exp) const {
  std::string pattern =
      query_pattern_processor_.ProcessAssignPattern(exp.to_match);
  return assign_pattern_storage_.GetPattern(lhs, pattern, exp.has_wildcard);
}

std::unordered_set<std::string> PatternManager::GetAllIfPattern() const {
  return if_pattern_storage_.GetAllIfPattern();
}

std::unordered_set<std::string> PatternManager::GetIfPattern(
    std::string var_ident) const {
  return if_pattern_storage_.GetIfPattern(var_ident);
}

std::unordered_set<std::string> PatternManager::GetPatternVariablesFromIf(
    int statement_number) const {
  return if_pattern_storage_.GetPatternVariablesFromIf(statement_number);
}

std::unordered_set<std::string> PatternManager::GetAllWhilePattern() const {
  return while_pattern_storage_.GetAllWhilePattern();
}

std::unordered_set<std::string> PatternManager::GetWhilePattern(
    std::string var_ident) const {
  return while_pattern_storage_.GetWhilePattern(var_ident);
}

std::unordered_set<std::string> PatternManager::GetPatternVariablesFromWhile(
    int statement_number) const {
  return while_pattern_storage_.GetPatternVariablesFromWhile(statement_number);
}
