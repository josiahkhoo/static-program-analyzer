#include "entity_manager.h"

ProcedureStorage EntityManager::procedureStore;
StatementStorage EntityManager::statementStore;
VariableStorage EntityManager::variableStore;
ConstantStorage EntityManager::constantStore;

EntityManager::EntityManager() {}

void EntityManager::AddProcedure(ProcedureEntity procedure) {
  procedureStore.AddProcedure(procedure);
}

void EntityManager::AddVariable(VariableEntity variable) {
  variableStore.AddVariable(variable);
}

void EntityManager::AddConstant(ConstantEntity constant) {
  constantStore.AddConstant(constant);
}

void EntityManager::AddCallStatement(CallEntity statement) {
  statementStore.AddCallStatement(statement);
}

void EntityManager::AddReadStatement(ReadEntity statement) {
  statementStore.AddReadStatement(statement);
}

void EntityManager::AddPrintStatement(PrintEntity statement) {
  statementStore.AddPrintStatement(statement);
}

void EntityManager::AddAssignStatement(AssignEntity statement) {
  statementStore.AddAssignStatement(statement);
}

void EntityManager::AddIfStatement(IfEntity statement) {
  statementStore.AddIfStatement(statement);
}

void EntityManager::AddWhileStatement(WhileEntity statement) {
  statementStore.AddWhileStatement(statement);
}

std::unordered_set<std::string> EntityManager::GetProcedures() {
  return procedureStore.GetProcedures();
}

std::unordered_set<std::string> EntityManager::GetVariables() {
  return variableStore.GetVariables();
}

std::unordered_set<std::string> EntityManager::GetConstants() {
  return constantStore.GetConstants();
}

std::unordered_set<std::string> EntityManager::GetStatements() {
  return statementStore.GetStatements();
}

std::unordered_set<std::string> EntityManager::GetCallStatements() {
  return statementStore.GetCallStatements();
}

std::unordered_set<std::string> EntityManager::GetReadStatements() {
  return statementStore.GetReadStatements();
}

std::unordered_set<std::string> EntityManager::GetPrintStatements() {
  return statementStore.GetPrintStatements();
}

std::unordered_set<std::string> EntityManager::GetAssignStatements() {
  return statementStore.GetAssignStatements();
}

std::unordered_set<std::string> EntityManager::GetIfStatements() {
  return statementStore.GetIfStatements();
}

std::unordered_set<std::string> EntityManager::GetWhileStatements() {
  return statementStore.GetWhileStatements();
}

void EntityManager::Clear() {
  procedureStore.Clear();
  statementStore.Clear();
  variableStore.Clear();
  constantStore.Clear();
}
