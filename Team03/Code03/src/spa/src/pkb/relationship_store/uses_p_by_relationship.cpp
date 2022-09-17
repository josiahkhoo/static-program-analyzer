#include "uses_p_by_relationship.h"

UsesPByRelationship::UsesPByRelationship(std::string variable_name)
    : variable_name_(variable_name) {}

void UsesPByRelationship::AddProcedure(std::string procedure_name) {
  procedure_list_.emplace(procedure_name);
}

std::unordered_set<std::string> UsesPByRelationship::GetUses() const {
  return procedure_list_;
}

void UsesPByRelationship::Clear() { procedure_list_.clear(); }
