#include "pattern_manager.h"

AssignPatternStorage PatternManager::assign_pattern_storage_;

PatternManager::PatternManager() {}

void PatternManager::AddAssignPattern(AssignEntity statement) {
  assign_pattern_storage_.AddAssignPattern(statement);
}

void PatternManager::Clear() {
  assign_pattern_storage_.Clear();
}
