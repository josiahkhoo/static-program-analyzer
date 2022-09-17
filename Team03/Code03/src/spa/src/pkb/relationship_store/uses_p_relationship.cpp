#include "uses_p_relationship.h"

UsesPRelationship::UsesPRelationship(std::string procedure_name)
    : procedure_name_(procedure_name) {}

void UsesPRelationship::AddVariable(std::string variable_name) {
  variable_list_.emplace(variable_name);
}

std::unordered_set<std::string> UsesPRelationship::GetVariables() const {
  return variable_list_;
}

void UsesPRelationship::Clear() { variable_list_.clear(); }
