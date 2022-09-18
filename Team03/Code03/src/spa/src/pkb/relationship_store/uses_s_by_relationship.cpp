#include "uses_s_by_relationship.h"

UsesSByRelationship::UsesSByRelationship(std::string variable_name)
    : variable_name_(variable_name) {}

void UsesSByRelationship::AddStatement(int statement_number) {
  statement_list_.emplace(statement_number);
}

std::unordered_set<int> UsesSByRelationship::GetUses() const {
  return statement_list_;
}

void UsesSByRelationship::Clear() { statement_list_.clear(); }
