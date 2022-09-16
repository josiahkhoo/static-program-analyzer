#include "uses_relationship.h"

UsesRelationship::UsesRelationship(std::string uses_name)
    : uses_name_(uses_name) {}

void UsesRelationship::AddVariable(std::string variable_name) {
  variable_list_.emplace(variable_name);
}

std::unordered_set<std::string> UsesRelationship::GetVariables() const {
  return variable_list_;
}

void UsesRelationship::Clear() { variable_list_.clear(); }
