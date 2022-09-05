#include "PKB.h"

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

EntityManager PKB::entityManager;

PKB::PKB() {}

void PKB::store(std::vector<ProcedureEntity> ts) {
  for (ProcedureEntity entity : ts) {
    entityManager.AddProcedure(entity);
  }
}

void PKB::store(std::vector<VariableEntity> ts) {
  for (VariableEntity entity : ts) {
    entityManager.AddVariable(entity);
  }
}

void PKB::store(std::vector<ConstantEntity> ts) {
  for (ConstantEntity entity : ts) {
    entityManager.AddConstant(entity);
  }
}

void PKB::store(std::vector<CallEntity> ts) {
  for (CallEntity entity : ts) {
    entityManager.AddCallStatement(entity);
  }
}

void PKB::store(std::vector<ReadEntity> ts) {
  for (ReadEntity entity : ts) {
    entityManager.AddReadStatement(entity);
  }
}

void PKB::store(std::vector<PrintEntity> ts) {
  for (PrintEntity entity : ts) {
    entityManager.AddPrintStatement(entity);
  }
}

void PKB::store(std::vector<AssignEntity> ts) {
  for (AssignEntity entity : ts) {
    entityManager.AddAssignStatement(entity);
  }
}

void PKB::store(std::vector<IfEntity> ts) {
  for (IfEntity entity : ts) {
    entityManager.AddIfStatement(entity);
  }
}

void PKB::store(std::vector<WhileEntity> ts) {
  for (WhileEntity entity : ts) {
    entityManager.AddWhileStatement(entity);
  }
}

void PKB::store(std::vector<FollowsAbstraction> abstractions) {
  for (FollowsAbstraction abstraction: abstractions) {
    relationshipManager.AddFollowsAbstraction(abstraction);
  }
}

std::unordered_set<std::string> PKB::QueryAll(EntityType type) {
  switch (type) {
    case PROCEDURE:
      return entityManager.GetProcedures();
    case CONSTANT:
      return entityManager.GetConstants();
    case VARIABLE:
      return entityManager.GetVariables();
    case STATEMENT:
      return entityManager.GetStatements();
    case CALL:
      return entityManager.GetCallStatements();
    case READ:
      return entityManager.GetReadStatements();
    case PRINT:
      return entityManager.GetPrintStatements();
    case ASSIGN:
      return entityManager.GetAssignStatements();
    case IF:
      return entityManager.GetIfStatements();
    case WHILE:
      return entityManager.GetWhileStatements();
  }
}

//std::unordered_set<std::string> PKB::QueryFollow(
//  int statement_number, EntityType type) {
//  return relationshipManager.getFollow(statement_number, entityManager.get(type));
//}
