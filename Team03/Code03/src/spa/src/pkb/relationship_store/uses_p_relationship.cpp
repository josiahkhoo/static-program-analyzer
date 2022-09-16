#include "uses_p_relationship.h"

UsesPRelationship::UsesPRelationship(std::string procedure_name)
    : procedure_name_(procedure_name) {}

void UsesPRelationship::AddVariable(VariableEntity variable) {
  variable_list_.emplace(variable.GetName());
}

std::unordered_set<std::string> UsesPRelationship::GetVariables() const {
  return variable_list_;
}
