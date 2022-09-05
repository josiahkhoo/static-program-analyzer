#include "variable_storage.h"

std::unordered_set<std::string> VariableStorage::variableList;

VariableStorage::VariableStorage() {}

void VariableStorage::AddVariable(VariableEntity variable) {
  variableList.emplace(variable.GetName());
}

std::unordered_set<std::string> VariableStorage::GetVariables() {
  return variableList;
}

void VariableStorage::Clear() { variableList.clear(); }
