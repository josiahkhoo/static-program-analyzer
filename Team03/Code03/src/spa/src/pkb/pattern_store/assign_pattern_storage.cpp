#include "assign_pattern_storage.h"

std::unordered_map<int, std::pair<std::string, std::string>> AssignPatternStorage::patterns_map_;

void AssignPatternStorage::AddAssignPattern(AssignEntity assignEntity) {
  int statement_number = assignEntity.GetStatementNumber();
  std::string lhs = assignEntity.GetLeftHandSidePattern();
  std::string rhs = assignEntity.GetRightHandSidePattern();
  patterns_map_.emplace(statement_number, std::pair<std::string, std::string>(lhs, rhs));
}