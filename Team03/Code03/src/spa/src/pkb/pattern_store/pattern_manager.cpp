#include "pattern_manager.h"

AssignPatternStorage PatternManager::assign_pattern_storage_;

PatternManager::PatternManager() {}

void PatternManager::AddAssignPattern(AssignEntity statement) {
  assign_pattern_storage_.AddAssignPattern(statement);
}

std::unordered_set<std::string> PatternManager::GetAllPattern(
    Expression exp) const {
  bool front_wildcard = exp.has_front_wildcard;
  bool back_wildcard = exp.has_back_wildcard;
  std::string pattern =
      query_pattern_processor_.ProcessAssignPattern(exp.to_match);
  return assign_pattern_storage_.GetAllPattern(pattern, front_wildcard,
                                               back_wildcard);
}

std::unordered_set<std::string> PatternManager::GetPattern(
    std::string lhs, Expression exp) const {
  bool front_wildcard = exp.has_front_wildcard;
  bool back_wildcard = exp.has_back_wildcard;
  std::string pattern =
      query_pattern_processor_.ProcessAssignPattern(exp.to_match);
  return assign_pattern_storage_.GetPattern(lhs, pattern, front_wildcard,
                                            back_wildcard);
}

void PatternManager::Clear() { assign_pattern_storage_.Clear(); }
