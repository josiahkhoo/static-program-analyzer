#include "entity_manager.h"

ProcedureStorage EntityManager::procedureStore;
StatementStorage EntityManager::statementStore;
VariableStorage EntityManager::variableStore;
ConstantStorage EntityManager::constantStore;

EntityManager::EntityManager() {}

void EntityManager::addProcedure(ProcedureEntity procedure) {
    procedureStore.addProcedure(procedure);
}

void EntityManager::addVariable(VariableEntity variable) {
    variableStore.addVariable(variable);
}

void EntityManager::addConstant(ConstantEntity constant) {
    constantStore.addConstant(constant);
}

void EntityManager::addCallStatement(CallEntity statement) {
    statementStore.addCallStatement(statement);
}

void EntityManager::addReadStatement(ReadEntity statement) {
    statementStore.addReadStatement(statement);
}

void EntityManager::addPrintStatement(PrintEntity statement) {
    statementStore.addPrintStatement(statement);
}

void EntityManager::addAssignStatement(AssignEntity statement) {
    statementStore.addAssignStatement(statement);
}

void EntityManager::addIfStatement(IfEntity statement) {
    statementStore.addIfStatement(statement);
}

void EntityManager::addWhileStatement(WhileEntity statement) {
    statementStore.addWhileStatement(statement);
}

void EntityManager::clear() {
    procedureStore.clear();
    statementStore.clear();
    variableStore.clear();
    constantStore.clear();
}
