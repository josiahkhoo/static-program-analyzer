#include "uses_s_relationship.h"

UsesSRelationship::UsesSRelationship(int statement_number)
    : statement_number_(statement_number) {}

void UsesSRelationship::AddVariable(std::string variable_name) {
  variable_list_.emplace(variable_name);
}

std::unordered_set<std::string> UsesSRelationship::GetVariables() const {
  return variable_list_;
}

void UsesSRelationship::Clear() { variable_list_.clear(); }
