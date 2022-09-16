#include "uses_by_relationship.h"

UsesByRelationship::UsesByRelationship(std::string variable_name)
    : variable_name_(variable_name) {}

void UsesByRelationship::AddUses(std::string uses_name) {
  uses_list_.emplace(uses_name);
}

std::unordered_set<std::string> UsesByRelationship::GetUses() const {
  return uses_list_;
}

void UsesByRelationship::Clear() { uses_list_.clear(); }
