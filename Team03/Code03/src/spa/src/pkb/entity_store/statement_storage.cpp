#include "statement_storage.h"

std::unordered_set<std::string> StatementStorage::statementList;
std::unordered_set<std::string> StatementStorage::callStatementList;
std::unordered_set<std::string> StatementStorage::readStatementList;
std::unordered_set<std::string> StatementStorage::printStatementList;
std::unordered_set<std::string> StatementStorage::assignStatementList;
std::unordered_set<std::string> StatementStorage::ifStatementList;
std::unordered_set<std::string> StatementStorage::whileStatementList;

StatementStorage::StatementStorage() {}

void StatementStorage::AddCallStatement(CallEntity callEntity) {
  callStatementList.emplace(std::to_string(callEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(callEntity.GetStatementNumber()));
}

void StatementStorage::AddReadStatement(ReadEntity readEntity) {
  readStatementList.emplace(std::to_string(readEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(readEntity.GetStatementNumber()));
}

void StatementStorage::AddPrintStatement(PrintEntity printEntity) {
  printStatementList.emplace(std::to_string(printEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(printEntity.GetStatementNumber()));
}

void StatementStorage::AddAssignStatement(AssignEntity assignEntity) {
  assignStatementList.emplace(
      std::to_string(assignEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(assignEntity.GetStatementNumber()));
}

void StatementStorage::AddIfStatement(IfEntity ifEntity) {
  ifStatementList.emplace(std::to_string(ifEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(ifEntity.GetStatementNumber()));
}

void StatementStorage::AddWhileStatement(WhileEntity whileEntity) {
  whileStatementList.emplace(std::to_string(whileEntity.GetStatementNumber()));
  statementList.emplace(std::to_string(whileEntity.GetStatementNumber()));
}

std::unordered_set<std::string> StatementStorage::GetStatements() {
  return statementList;
}

std::unordered_set<std::string> StatementStorage::GetCallStatements() {
  return callStatementList;
}

std::unordered_set<std::string> StatementStorage::GetReadStatements() {
  return readStatementList;
}

std::unordered_set<std::string> StatementStorage::GetPrintStatements() {
  return printStatementList;
}

std::unordered_set<std::string> StatementStorage::GetAssignStatements() {
  return assignStatementList;
}

std::unordered_set<std::string> StatementStorage::GetIfStatements() {
  return ifStatementList;
}

std::unordered_set<std::string> StatementStorage::GetWhileStatements() {
  return whileStatementList;
}

void StatementStorage::Clear() {
  statementList.clear();
  callStatementList.clear();
  readStatementList.clear();
  printStatementList.clear();
  assignStatementList.clear();
  ifStatementList.clear();
  whileStatementList.clear();
}
