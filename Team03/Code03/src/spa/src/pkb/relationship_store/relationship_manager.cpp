#include "relationship_manager.h"

void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(ParentAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
};

void RelationshipManager::AddAbstraction(ParentTAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(UsesPAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(UsesSAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(ModifiesPAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

void RelationshipManager::AddAbstraction(ModifiesSAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements()
    const {
  return follows_store_.GetFollowsStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsStatements(
    int statement_number) const {
  return follows_store_.GetFollowsStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements()
    const {
  return follows_store_.GetFollowsByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetFollowsTByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentStatements()
    const {
  return parent_store_.GetParentStatements();
}

std::unordered_set<std::string> RelationshipManager::GetParentStatements(
    int statement_number) const {
  return parent_store_.GetParentStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentTStatements(
    int statement_number) const {
  return parent_store_.GetParentTStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentByStatements(
    int statement_number) const {
  return parent_store_.GetParentByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetParentByStatements()
    const {
  return parent_store_.GetParentByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetParentTByStatements(
    int statement_number) const {
  return parent_store_.GetParentTByStatements(statement_number);
}

std::unordered_set<std::string> RelationshipManager::GetUsingProcedures()
    const {
  return uses_store_.GetUsingProcedures();
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedure(
    std::string procedure_name) const {
  return uses_store_.GetVariablesUsedByProcedure(procedure_name);
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedures() const {
  return uses_store_.GetVariablesUsedByProcedures();
}

std::unordered_set<std::string> RelationshipManager::GetProceduresUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetProceduresUsingVariable(variable_name);
}

std::unordered_set<std::string> RelationshipManager::GetUsingStatements()
    const {
  return uses_store_.GetUsingStatements();
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatement(int statement_number) const {
  return uses_store_.GetVariablesUsedByStatement(statement_number);
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatements() const {
  return uses_store_.GetVariablesUsedByStatements();
}

std::unordered_set<std::string> RelationshipManager::GetStatementsUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetStatementsUsingVariable(variable_name);
}

std::unordered_set<std::string> RelationshipManager::GetModifyingProcedures()
    const {
  return modifies_store_.GetModifyingProcedures();
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedure(
    std::string procedure_name) const {
  return modifies_store_.GetVariablesModifiedByProcedure(procedure_name);
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedures() const {
  return modifies_store_.GetVariablesModifiedByProcedures();
}

std::unordered_set<std::string>
RelationshipManager::GetProceduresModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetProceduresModifyingVariable(variable_name);
}

std::unordered_set<std::string> RelationshipManager::GetModifyingStatements()
    const {
  return modifies_store_.GetModifyingStatements();
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatement(
    int statement_number) const {
  return modifies_store_.GetVariablesModifiedByStatement(statement_number);
}

std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatements() const {
  return modifies_store_.GetVariablesModifiedByStatements();
}

std::unordered_set<std::string>
RelationshipManager::GetStatementsModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetStatementsModifyingVariable(variable_name);
}

void RelationshipManager::Clear() {
  //  follows_store_.Clear();
  parent_store_.Clear();
  modifies_store_.Clear();
}
