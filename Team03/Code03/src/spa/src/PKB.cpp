#include "PKB.h"

#include <stdexcept>
#include <vector>

EntityManager PKB::entityManager;
RelationshipManager PKB::relationshipManager;

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
  std::unordered_set<std::string> statements =
      relationshipManager.GetFollowsStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  std::set_union(statements.begin(), statements.end(), typed_statements.begin(),
                 typed_statements.end(), std::inserter(result, result.begin()));
  return result;
}

std::unordered_set<std::string> PKB::QueryAllFollowBy(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationshipManager.GetFollowsByStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  std::set_union(statements.begin(), statements.end(), typed_statements.begin(),
                 typed_statements.end(), std::inserter(result, result.begin()));
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowBy(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationshipManager.GetFollowsByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  std::set_union(statements.begin(), statements.end(), typed_statements.begin(),
                 typed_statements.end(), std::inserter(result, result.begin()));
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowT(int statement_number,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationshipManager.GetFollowsTStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  std::set_union(statements.begin(), statements.end(), typed_statements.begin(),
                 typed_statements.end(), std::inserter(result, result.begin()));
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowTBy(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationshipManager.GetFollowsTByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  std::set_union(statements.begin(), statements.end(), typed_statements.begin(),
                 typed_statements.end(), std::inserter(result, result.begin()));
  return result;
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
  return relationshipManager.GetFollowsStatements(statement_number);
}
