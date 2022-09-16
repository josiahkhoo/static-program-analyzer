#include "uses_s_relationship.h"

UsesSRelationship::UsesSRelationship(std::string statement_number)
    : statement_number_(statement_number) {}

void UsesSRelationship::AddVariable(VariableEntity variable) {
  variable_list_.emplace(variable.GetName());
}

std::unordered_set<std::string> UsesSRelationship::GetVariables() const {
  return variable_list_;
}

void UsesSRelationship::Clear() { variable_list_.clear(); }
