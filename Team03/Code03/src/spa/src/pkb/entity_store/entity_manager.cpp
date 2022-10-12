#include "entity_manager.h"

EntityManager::EntityManager() {}

void EntityManager::AddProcedure(ProcedureEntity procedure) {
  procedure_store_.AddProcedure(procedure);
}

void EntityManager::AddVariable(VariableEntity variable) {
  variable_store_.AddVariable(variable);
}

void EntityManager::AddConstant(ConstantEntity constant) {
  constant_store_.AddConstant(constant);
}

void EntityManager::AddCallStatement(CallEntity statement) {
  statement_store_.AddCallStatement(statement);
}

void EntityManager::AddReadStatement(ReadEntity statement) {
  statement_store_.AddReadStatement(statement);
}

void EntityManager::AddPrintStatement(PrintEntity statement) {
  statement_store_.AddPrintStatement(statement);
}

void EntityManager::AddAssignStatement(AssignEntity statement) {
  statement_store_.AddAssignStatement(statement);
}

void EntityManager::AddIfStatement(IfEntity statement) {
  statement_store_.AddIfStatement(statement);
}

void EntityManager::AddWhileStatement(WhileEntity statement) {
  statement_store_.AddWhileStatement(statement);
}

std::unordered_set<std::string> EntityManager::GetProcedures() const {
  return procedure_store_.GetProcedures();
}

std::unordered_set<std::string> EntityManager::GetVariables() const {
  return variable_store_.GetVariables();
}

std::unordered_set<std::string> EntityManager::GetConstants() const {
  return constant_store_.GetConstants();
}

std::unordered_set<std::string> EntityManager::GetStatements() const {
  return statement_store_.GetStatements();
}

std::unordered_set<std::string> EntityManager::GetCallStatements() const {
  return statement_store_.GetCallStatements();
}

std::unordered_set<std::string> EntityManager::GetCallStatements(
    std::string proc) const {
  return statement_store_.GetCallStatements(proc);
}

std::string EntityManager::GetCallStatementProcedure(
    int statement_number) const {
  return statement_store_.GetCallStatementProcedure(statement_number);
}

std::unordered_set<std::string> EntityManager::GetReadStatements() const {
  return statement_store_.GetReadStatements();
}

std::unordered_set<std::string> EntityManager::GetReadStatements(
    std::string var) const {
  return statement_store_.GetReadStatements(var);
}

std::string EntityManager::GetReadStatementVariable(
    int statement_number) const {
  return statement_store_.GetReadStatementVariable(statement_number);
}

std::unordered_set<std::string> EntityManager::GetPrintStatements() const {
  return statement_store_.GetPrintStatements();
}

std::unordered_set<std::string> EntityManager::GetPrintStatements(
    std::string var) const {
  return statement_store_.GetPrintStatements(var);
}

std::string EntityManager::GetPrintStatementVariable(
    int statement_number) const {
  return statement_store_.GetPrintStatementVariable(statement_number);
}

std::unordered_set<std::string> EntityManager::GetAssignStatements() const {
  return statement_store_.GetAssignStatements();
}

std::unordered_set<std::string> EntityManager::GetIfStatements() const {
  return statement_store_.GetIfStatements();
}

std::unordered_set<std::string> EntityManager::GetWhileStatements() const {
  return statement_store_.GetWhileStatements();
}
