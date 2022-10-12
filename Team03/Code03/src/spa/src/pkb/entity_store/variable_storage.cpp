#include "variable_storage.h"

VariableStorage::VariableStorage() {}

void VariableStorage::AddVariable(VariableEntity variable) {
  variableList.emplace(variable.GetName());
}

std::unordered_set<std::string> VariableStorage::GetVariables() const {
  return variableList;
}
