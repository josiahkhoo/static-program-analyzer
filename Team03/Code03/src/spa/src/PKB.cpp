#include "PKB.h"

#include <stdexcept>
#include <vector>

PKB::PKB() {}

void PKB::Store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entity_manager_.AddProcedure(entity);
  }
}

void PKB::Store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entity_manager_.AddVariable(entity);
  }
}

void PKB::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}

void PKB::Store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entity_manager_.AddCallStatement(entity);
  }
}

void PKB::Store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entity_manager_.AddReadStatement(entity);
  }
}

void PKB::Store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entity_manager_.AddPrintStatement(entity);
  }
}

void PKB::Store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entity_manager_.AddAssignStatement(entity);
    pattern_manager_.AddAssignPattern(entity);
  }
}

void PKB::Store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entity_manager_.AddIfStatement(entity);
  }
}

void PKB::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}

void PKB::Store(std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ParentAbstraction> abstractions) {
  for (const ParentAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ParentTAbstraction> abstractions) {
  for (const ParentTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<UsesSAbstraction> abstractions) {
  for (const UsesSAbstraction& abstraction : abstractions) {
    // relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<UsesPAbstraction> abstractions) {
  for (const UsesPAbstraction& abstraction : abstractions) {
    // relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ModifiesSAbstraction> abstractions) {
  for (const ModifiesSAbstraction& abstraction : abstractions) {
    // relationship_manager_.AddAbstraction(abstraction);
  }
}

void PKB::Store(std::vector<ModifiesPAbstraction> abstractions) {
  for (const ModifiesPAbstraction& abstraction : abstractions) {
    // relationship_manager_.AddAbstraction(abstraction);
  }
}

std::unordered_set<std::string> PKB::QueryAll(EntityType type) const {
  switch (type) {
    case PROCEDURE:
      return entity_manager_.GetProcedures();
    case CONSTANT:
      return entity_manager_.GetConstants();
    case VARIABLE:
      return entity_manager_.GetVariables();
    case STATEMENT:
      return entity_manager_.GetStatements();
    case CALL:
      return entity_manager_.GetCallStatements();
    case READ:
      return entity_manager_.GetReadStatements();
    case PRINT:
      return entity_manager_.GetPrintStatements();
    case ASSIGN:
      return entity_manager_.GetAssignStatements();
    case IF:
      return entity_manager_.GetIfStatements();
    case WHILE:
      return entity_manager_.GetWhileStatements();
  }
}

std::unordered_set<std::string> PKB::QueryAllFollows(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllFollowsBy(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsByStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllFollowsRelations() const {
  return {};
}

std::unordered_set<std::string> PKB::QueryFollows(int statement_number,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowsBy(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowsT(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsTStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  };
  return result;
}

std::unordered_set<std::string> PKB::QueryFollowsTBy(int statement_number,
                                                     EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetFollowsTByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllParent(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllParentBy(EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentByStatements();
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllParentsRelations() const {
  return {};
}

std::unordered_set<std::string> PKB::QueryParent(int statement_number,
                                                 EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryParentBy(int statement_number,
                                                   EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryParentT(int statement_number,
                                                  EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentTStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  };
  return result;
}

std::unordered_set<std::string> PKB::QueryParentTBy(int statement_number,
                                                    EntityType type) const {
  std::unordered_set<std::string> statements =
      relationship_manager_.GetParentTByStatements(statement_number);
  std::unordered_set<std::string> typed_statements = QueryAll(type);
  std::unordered_set<std::string> result;
  for (const std::string& statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}

std::unordered_set<std::string> PKB::QueryAllUses(EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryAllUsesBy(EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryAllUsesRelations() const {
  return {};
}

std::unordered_set<std::string> PKB::QueryUsesS(int statement_number,
                                                EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryUsesSBy(std::string identifier,
                                                  EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryUsesP(std::string identifier,
                                                EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryUsesPBy(std::string identifier,
                                                  EntityType type) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryAllPattern(Expression exp) const {
  return pattern_manager_.GetAllPattern(exp);
}

std::unordered_set<std::string> PKB::QueryPattern(EntityType type,
                                                  Expression exp) const {
  return {};
}

std::unordered_set<std::string> PKB::QueryPattern(std::string lhs,
                                                  Expression exp) const {
  return pattern_manager_.GetPattern(lhs, exp);
}
