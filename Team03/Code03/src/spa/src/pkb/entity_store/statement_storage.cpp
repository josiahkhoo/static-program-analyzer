#include "statement_storage.h"

std::unordered_set<int> StatementStorage::callStatementList;
std::unordered_set<int> StatementStorage::readStatementList;
std::unordered_set<int> StatementStorage::printStatementList;
std::unordered_set<int> StatementStorage::assignStatementList;
std::unordered_set<int> StatementStorage::ifStatementList;
std::unordered_set<int> StatementStorage::whileStatementList;

StatementStorage::StatementStorage() {}

void StatementStorage::addCallStatement(CallEntity callEntity) {
    callStatementList.emplace(callEntity.GetLineNumber());
}

void StatementStorage::addReadStatement(ReadEntity readEntity) {
    readStatementList.emplace(readEntity.GetLineNumber());
}

void StatementStorage::addPrintStatement(PrintEntity printEntity) {
    printStatementList.emplace(printEntity.GetLineNumber());
}

void StatementStorage::addAssignStatement(AssignEntity assignEntity) {
    assignStatementList.emplace(assignEntity.GetLineNumber());
}

void StatementStorage::addIfStatement(IfEntity ifEntity) {
    ifStatementList.emplace(ifEntity.GetLineNumber());
}

void StatementStorage::addWhileStatement(WhileEntity whileEntity) {
    whileStatementList.emplace(whileEntity.GetLineNumber());
}

std::unordered_set<int> StatementStorage::getCallStatements() {
    return callStatementList;
}

std::unordered_set<int> StatementStorage::getReadStatements() {
    return readStatementList;
}

std::unordered_set<int> StatementStorage::getPrintStatements() {
    return printStatementList;
}

std::unordered_set<int> StatementStorage::getAssignStatements() {
    return assignStatementList;
}

std::unordered_set<int> StatementStorage::getIfStatements() {
    return ifStatementList;
}

std::unordered_set<int> StatementStorage::getWhileStatements() {
    return whileStatementList;
}

void StatementStorage::clear() {
    callStatementList.clear();
    readStatementList.clear();
    printStatementList.clear();
    assignStatementList.clear();
    ifStatementList.clear();
    whileStatementList.clear();
}
