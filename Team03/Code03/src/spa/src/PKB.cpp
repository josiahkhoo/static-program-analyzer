#include "PKB.h"

#include <stdexcept>
#include <vector>

EntityManager PKB::entityManager;

PKB::PKB() {}

void PKB::store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entityManager.AddProcedure(entity);
  }
}

void PKB::store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entityManager.AddVariable(entity);
  }
}

void PKB::store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entityManager.AddConstant(entity);
  }
}

void PKB::store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entityManager.AddCallStatement(entity);
  }
}

void PKB::store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entityManager.AddReadStatement(entity);
  }
}

void PKB::store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entityManager.AddPrintStatement(entity);
  }
}

void PKB::store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entityManager.AddAssignStatement(entity);
  }
}

void PKB::store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entityManager.AddIfStatement(entity);
  }
}

void PKB::store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entityManager.AddWhileStatement(entity);
  }
}

void PKB::store(std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationshipManager.AddAbstraction(abstraction);
  }
}

void PKB::store(std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationshipManager.AddAbstraction(abstraction);
  }
}

std::unordered_set<std::string> PKB::QueryAllFollow(EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsStatements();
    case CALL:
      return relationshipManager.GetFollowsCallStatements();
    case READ:
      return relationshipManager.GetFollowsReadStatements();
    case PRINT:
      return relationshipManager.GetFollowsPrintStatements();
    case ASSIGN:
      return relationshipManager.GetFollowsAssignStatements();
    case IF:
      return relationshipManager.GetFollowsIfStatements();
    case WHILE:
      return relationshipManager.GetFollowsWhileStatements();
    default:
      throw std::runtime_error("Invalid entity type");
  }
}

std::unordered_set<std::string> PKB::QueryAllFollowBy(EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsByStatements();
    case CALL:
      return relationshipManager.GetFollowsByCallStatements();
    case READ:
      return relationshipManager.GetFollowsByReadStatements();
    case PRINT:
      return relationshipManager.GetFollowsByPrintStatements();
    case ASSIGN:
      return relationshipManager.GetFollowsByAssignStatements();
    case IF:
      return relationshipManager.GetFollowsByIfStatements();
    case WHILE:
      return relationshipManager.GetFollowsByWhileStatements();
    default:
      throw std::runtime_error("Invalid entity type");
  }
}

std::unordered_set<std::string> PKB::QueryFollowBy(int statement_number,
                                                   EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsByStatements(statement_number);
    case CALL:
      return relationshipManager.GetFollowsByCallStatements(statement_number);
    case READ:
      return relationshipManager.GetFollowsByReadStatements(statement_number);
    case PRINT:
      return relationshipManager.GetFollowsByPrintStatements(statement_number);
    case ASSIGN:
      return relationshipManager.GetFollowsByAssignStatements(statement_number);
    case IF:
      return relationshipManager.GetFollowsByIfStatements(statement_number);
    case WHILE:
      return relationshipManager.GetFollowsByWhileStatements(statement_number);
    default:
      throw std::runtime_error("Invalid entity type");
  }
}

std::unordered_set<std::string> PKB::QueryFollowT(int statement_number,
                                                  EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsTStatements(statement_number);
    case CALL:
      return relationshipManager.GetFollowsTCallStatements(statement_number);
    case READ:
      return relationshipManager.GetFollowsTReadStatements(statement_number);
    case PRINT:
      return relationshipManager.GetFollowsTPrintStatements(statement_number);
    case ASSIGN:
      return relationshipManager.GetFollowsTAssignStatements(statement_number);
    case IF:
      return relationshipManager.GetFollowsTIfStatements(statement_number);
    case WHILE:
      return relationshipManager.GetFollowsTWhileStatements(statement_number);
    default:
      throw std::runtime_error("Invalid entity type");
  }
}

std::unordered_set<std::string> PKB::QueryFollowTBy(int statement_number,
                                                    EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsTByStatements(statement_number);
    case CALL:
      return relationshipManager.GetFollowsTByCallStatements(statement_number);
    case READ:
      return relationshipManager.GetFollowsTByReadStatements(statement_number);
    case PRINT:
      return relationshipManager.GetFollowsTByPrintStatements(statement_number);
    case ASSIGN:
      return relationshipManager.GetFollowsTByAssignStatements(
          statement_number);
    case IF:
      return relationshipManager.GetFollowsTByIfStatements(statement_number);
    case WHILE:
      return relationshipManager.GetFollowsTByWhileStatements(statement_number);
    default:
      throw std::runtime_error("Invalid entity type");
  }
}

std::unordered_set<std::string> PKB::QueryAll(EntityType type) const {
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

std::unordered_set<std::string> PKB::QueryFollow(int statement_number,
                                                 EntityType type) const {
  switch (type) {
    case STATEMENT:
      return relationshipManager.GetFollowsStatements(statement_number);
    case CALL:
      return relationshipManager.GetFollowsCallStatements(statement_number);
    case READ:
      return relationshipManager.GetFollowsReadStatements(statement_number);
    case PRINT:
      return relationshipManager.GetFollowsPrintStatements(statement_number);
    case ASSIGN:
      return relationshipManager.GetFollowsAssignStatements(statement_number);
    case IF:
      return relationshipManager.GetFollowsIfStatements(statement_number);
    case WHILE:
      return relationshipManager.GetFollowsWhileStatements(statement_number);
    default:
      throw std::runtime_error("Invalid entity type");
  }
}
