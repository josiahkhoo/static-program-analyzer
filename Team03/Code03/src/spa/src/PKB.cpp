#include "PKB.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

EntityManager PKB::entityManager;

PKB::PKB() {}

void PKB::store(std::vector<ProcedureEntity> ts) {
    for (ProcedureEntity entity : ts) {
        entityManager.addProcedure(entity);
    }
}

void PKB::store(std::vector<VariableEntity> ts) {
    for (VariableEntity entity : ts) {
        entityManager.addVariable(entity);
    }
}

void PKB::store(std::vector<ConstantEntity> ts) {
    for (ConstantEntity entity : ts) {
        entityManager.addConstant(entity);
    }
}

void PKB::store(std::vector<CallEntity> ts) {
    for (CallEntity entity : ts) {
        entityManager.addCallStatement(entity);
    }
}

void PKB::store(std::vector<ReadEntity> ts) {
    for (ReadEntity entity : ts) {
        entityManager.addReadStatement(entity);
    }
}

void PKB::store(std::vector<PrintEntity> ts) {
    for (PrintEntity entity : ts) {
        entityManager.addPrintStatement(entity);
    }
}

void PKB::store(std::vector<AssignEntity> ts) {
    for (AssignEntity entity : ts) {
        entityManager.addAssignStatement(entity);
    }
}

void PKB::store(std::vector<IfEntity> ts) {
    for (IfEntity entity : ts) {
        entityManager.addIfStatement(entity);
    }
}

void PKB::store(std::vector<WhileEntity> ts) {
    for (WhileEntity entity : ts) {
        entityManager.addWhileStatement(entity);
    }
}

std::unordered_set<std::string> queryAllProcedures() {}
