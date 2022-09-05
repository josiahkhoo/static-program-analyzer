#include "statement_storage.h"

std::unordered_set<std::string> StatementStorage::statementList;
std::unordered_set<std::string> StatementStorage::callStatementList;
std::unordered_set<std::string> StatementStorage::readStatementList;
std::unordered_set<std::string> StatementStorage::printStatementList;
std::unordered_set<std::string> StatementStorage::assignStatementList;
std::unordered_set<std::string> StatementStorage::ifStatementList;
std::unordered_set<std::string> StatementStorage::whileStatementList;

StatementStorage::StatementStorage() {}

void StatementStorage::addCallStatement(CallEntity callEntity) {
    callStatementList.emplace(std::to_string(callEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(callEntity.GetStatementNumber()));
}

void StatementStorage::addReadStatement(ReadEntity readEntity) {
    readStatementList.emplace(std::to_string(readEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(readEntity.GetStatementNumber()));
}

void StatementStorage::addPrintStatement(PrintEntity printEntity) {
    printStatementList.emplace(std::to_string(printEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(printEntity.GetStatementNumber()));
}

void StatementStorage::addAssignStatement(AssignEntity assignEntity) {
    assignStatementList.emplace(std::to_string(assignEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(assignEntity.GetStatementNumber()));
}

void StatementStorage::addIfStatement(IfEntity ifEntity) {
    ifStatementList.emplace(std::to_string(ifEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(ifEntity.GetStatementNumber()));
}

void StatementStorage::addWhileStatement(WhileEntity whileEntity) {
    whileStatementList.emplace(std::to_string(whileEntity.GetStatementNumber()));
    statementList.emplace(std::to_string(whileEntity.GetStatementNumber()));
}

std::unordered_set<std::string> StatementStorage::getStatements() {
    return statementList;
}

std::unordered_set<std::string> StatementStorage::getCallStatements() {
    return callStatementList;
}

std::unordered_set<std::string> StatementStorage::getReadStatements() {
    return readStatementList;
}

std::unordered_set<std::string> StatementStorage::getPrintStatements() {
    return printStatementList;
}

std::unordered_set<std::string> StatementStorage::getAssignStatements() {
    return assignStatementList;
}

std::unordered_set<std::string> StatementStorage::getIfStatements() {
    return ifStatementList;
}

std::unordered_set<std::string> StatementStorage::getWhileStatements() {
    return whileStatementList;
}

void StatementStorage::clear() {
    statementList.clear();
    callStatementList.clear();
    readStatementList.clear();
    printStatementList.clear();
    assignStatementList.clear();
    ifStatementList.clear();
    whileStatementList.clear();
}
