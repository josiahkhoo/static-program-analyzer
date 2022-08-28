#include "variable_storage.h"

std::unordered_set<std::string> VariableStorage::variableList;

VariableStorage::VariableStorage() {}

void VariableStorage::addVariable(VariableEntity variable) {
    variableList.emplace(variable.GetName());
}

std::unordered_set<std::string> VariableStorage::getVariables() {
    return variableList;
}

void VariableStorage::clear() {
    variableList.clear();
}
