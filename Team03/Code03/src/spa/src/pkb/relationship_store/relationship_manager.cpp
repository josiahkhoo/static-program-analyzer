#include "relationship_manager.h"

/** ====================================
 * General Relationship Adder Methods
 * ==================================== */
/// Add Follows Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(FollowsAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

/// Add FollowsT Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(FollowsTAbstraction abstraction) {
  follows_store_.AddRelationship(abstraction);
}

/// Add Parent Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ParentAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

/// Add ParentT Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ParentTAbstraction abstraction) {
  parent_store_.AddRelationship(abstraction);
}

/// Add Procedure Uses Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(UsesPAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

/// Add Statement Uses Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(UsesSAbstraction abstraction) {
  uses_store_.AddRelationship(abstraction);
}

/// Add Procedure Modifies Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ModifiesPAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

/// Add Statement Modifies Relationship
/// \param abstraction
void RelationshipManager::AddAbstraction(ModifiesSAbstraction abstraction) {
  modifies_store_.AddRelationship(abstraction);
}

/** ====================================
 * General Relationship Getter Methods
 * ==================================== */
/// GetFollowsStatements
/// \return Gets all statements following any statement
std::unordered_set<std::string> RelationshipManager::GetFollowsStatements()
    const {
  return follows_store_.GetFollowsStatements();
}

/// GetFollowsStatements
/// \param statement_number
/// \return Gets all statements directly following a specified statement
std::unordered_set<std::string> RelationshipManager::GetFollowsStatements(
    int statement_number) const {
  return follows_store_.GetFollowsStatements(statement_number);
}

/// GetFollowsTStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetFollowsTStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTStatements(statement_number);
}

/// GetFollowsByStatements
/// \param statement_number
/// \return Gets all statements directly followed by a specified statement
std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsByStatements(statement_number);
}

/// GetFollowsByStatements
/// \return Gets all statements followed by any statement
std::unordered_set<std::string> RelationshipManager::GetFollowsByStatements()
    const {
  return follows_store_.GetFollowsByStatements();
}

/// GetFollowsTByStatements
/// \param statement_number
/// \return Gets all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetFollowsTByStatements(
    int statement_number) const {
  return follows_store_.GetFollowsTByStatements(statement_number);
}

/// GetParentStatements
/// \return Gets all statements that are direct parents of any statement
std::unordered_set<std::string> RelationshipManager::GetParentStatements()
    const {
  return parent_store_.GetParentStatements();
}

/// GetParentStatements
/// \param statement_number
/// \return Gets all statements that are direct parents of a specified statement
std::unordered_set<std::string> RelationshipManager::GetParentStatements(
    int statement_number) const {
  return parent_store_.GetParentStatements(statement_number);
}

/// GetParentTStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> RelationshipManager::GetParentTStatements(
    int statement_number) const {
  return parent_store_.GetParentTStatements(statement_number);
}

/// GetParentByStatements
/// \param statement_number
/// \return Gets all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> RelationshipManager::GetParentByStatements(
    int statement_number) const {
  return parent_store_.GetParentByStatements(statement_number);
}

/// GetParentByStatements
/// \return Gets all statements that are direct children of any statement
std::unordered_set<std::string> RelationshipManager::GetParentByStatements()
    const {
  return parent_store_.GetParentByStatements();
}

/// GetParentTByStatements
/// \param statement_number
/// \return Gets all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> RelationshipManager::GetParentTByStatements(
    int statement_number) const {
  return parent_store_.GetParentTByStatements(statement_number);
}

/// GetUsingProcedures
/// \return Gets all procedures that use variables
std::unordered_set<std::string> RelationshipManager::GetUsingProcedures()
    const {
  return uses_store_.GetUsingProcedures();
}

/// GetVariablesUsedByProcedure
/// \param procedure_name
/// \return Gets all variables used by a specified procedure
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedure(
    std::string procedure_name) const {
  return uses_store_.GetVariablesUsedByProcedure(procedure_name);
}

/// GetVariablesUsedByProcedures
/// \return Gets all variables that are used by procedures
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByProcedures() const {
  return uses_store_.GetVariablesUsedByProcedures();
}

/// GetProceduresUsingVariable
/// \param variable_name
/// \return Gets all procedures that use a specified variable
std::unordered_set<std::string> RelationshipManager::GetProceduresUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetProceduresUsingVariable(variable_name);
}

/// GetUsingStatements
/// \return Gets all statements that use variables
std::unordered_set<std::string> RelationshipManager::GetUsingStatements()
    const {
  return uses_store_.GetUsingStatements();
}

/// GetVariablesUsedByStatement
/// \param statement_number
/// \return Gets all variables used by a specified statement
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatement(int statement_number) const {
  return uses_store_.GetVariablesUsedByStatement(statement_number);
}

/// GetVariablesUsedByStatements
/// \return Gets all variables that are used by statements
std::unordered_set<std::string>
RelationshipManager::GetVariablesUsedByStatements() const {
  return uses_store_.GetVariablesUsedByStatements();
}

/// GetStatementsUsingVariable
/// \param variable_name
/// \return Gets all statements that use a specified variable
std::unordered_set<std::string> RelationshipManager::GetStatementsUsingVariable(
    std::string variable_name) const {
  return uses_store_.GetStatementsUsingVariable(variable_name);
}

/// GetModifyingProcedures
/// \return Gets all procedures that modify variables
std::unordered_set<std::string> RelationshipManager::GetModifyingProcedures()
    const {
  return modifies_store_.GetModifyingProcedures();
}

/// GetVariablesModifiedByProcedure
/// \param procedure_name
/// \return Gets all variables modified by a specified procedure
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedure(
    std::string procedure_name) const {
  return modifies_store_.GetVariablesModifiedByProcedure(procedure_name);
}

/// GetVariablesModifiedByProcedures
/// \return Gets all variables that are modified by procedures
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByProcedures() const {
  return modifies_store_.GetVariablesModifiedByProcedures();
}

/// GetProceduresModifyingVariable
/// \param variable_name
/// \return Gets all procedures that modify a specified variable
std::unordered_set<std::string>
RelationshipManager::GetProceduresModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetProceduresModifyingVariable(variable_name);
}

/// GetModifyingStatements
/// \return Gets all statements that modify variables
std::unordered_set<std::string> RelationshipManager::GetModifyingStatements()
    const {
  return modifies_store_.GetModifyingStatements();
}

/// GetVariablesModifiedByStatement
/// \param statement_number
/// \return Gets all variables modified by a specified statement
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatement(
    int statement_number) const {
  return modifies_store_.GetVariablesModifiedByStatement(statement_number);
}

/// GetVariablesModifiedByStatements
/// \return Gets all variables that are modified by statements
std::unordered_set<std::string>
RelationshipManager::GetVariablesModifiedByStatements() const {
  return modifies_store_.GetVariablesModifiedByStatements();
}

/// GetStatementsModifyingVariable
/// \param variable_name
/// \return Gets all statements that modify a specified variable
std::unordered_set<std::string>
RelationshipManager::GetStatementsModifyingVariable(
    std::string variable_name) const {
  return modifies_store_.GetStatementsModifyingVariable(variable_name);
}

void RelationshipManager::Clear() {
  follows_store_.Clear();
  parent_store_.Clear();
  modifies_store_.Clear();
}
