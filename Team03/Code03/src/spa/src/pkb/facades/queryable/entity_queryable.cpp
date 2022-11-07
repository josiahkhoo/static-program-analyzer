#include "entity_queryable.h"

EntityQueryable::EntityQueryable(const EntityManager& entity_manager_)
    : entity_manager_(entity_manager_) {}

std::unordered_set<std::string> EntityQueryable::QueryAll(
    EntityType type) const {
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

std::unordered_set<std::string> EntityQueryable::GetAssignStatements() const {
  return entity_manager_.GetAssignStatements();
}

std::unordered_set<std::string> EntityQueryable::GetCallStatements() const {
  return entity_manager_.GetCallStatements();
}

std::unordered_set<std::string> EntityQueryable::GetReadStatements() const {
  return entity_manager_.GetReadStatements();
}

std::string EntityQueryable::QueryWithAttributeFromStatement(
    EntityType type, int statement_number) const {
  std::string result;
  if (type == EntityType::CALL) {
    result = entity_manager_.GetCallStatementProcedure(statement_number);
  } else if (type == EntityType::PRINT) {
    result = entity_manager_.GetPrintStatementVariable(statement_number);
  } else if (type == EntityType::READ) {
    result = entity_manager_.GetReadStatementVariable(statement_number);
  }
  return result;
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute proc_name or var_name
/// \param identifier proc_name/var_name
/// \return Query entities that matches attribute proc_name or var_name
std::unordered_set<std::string> EntityQueryable::QueryWithAttribute(
    EntityType type, AttributeName name, std::string identifier) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::PROCEDURE && name == AttributeName::PROC_NAME) {
    std::unordered_set<std::string> procedures =
        entity_manager_.GetProcedures();
    if (procedures.find(identifier) != procedures.end()) {
      result.emplace(identifier);
    }
  } else if (type == EntityType::CALL && name == AttributeName::PROC_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetCallStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  } else if (type == EntityType::VARIABLE && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> variables = entity_manager_.GetVariables();
    if (variables.find(identifier) != variables.end()) {
      result.emplace(identifier);
    }
  } else if (type == EntityType::READ && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetReadStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  } else if (type == EntityType::PRINT && name == AttributeName::VAR_NAME) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetPrintStatements(identifier);
    for (const std::string& stmt : statements) {
      result.emplace(stmt);
    }
  }
  return result;
}

/// QueryWithAttribute
/// \param type Entity type
/// \param name Attribute value or stmt_no
/// \param number value/stmt_no
/// \return Query entities that matches attribute value or stmt_no
std::unordered_set<std::string> EntityQueryable::QueryWithAttribute(
    EntityType type, AttributeName name, int number) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT && name == AttributeName::VALUE) {
    std::unordered_set<std::string> constants = entity_manager_.GetConstants();
    if (constants.find(std::to_string(number)) != constants.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::STATEMENT && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::READ && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetReadStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::PRINT && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetPrintStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::CALL && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetCallStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::WHILE && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetWhileStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::IF && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetIfStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  } else if (type == EntityType::ASSIGN && name == AttributeName::STMT_NO) {
    std::unordered_set<std::string> statements =
        entity_manager_.GetAssignStatements();
    if (statements.find(std::to_string(number)) != statements.end()) {
      result.emplace(std::to_string(number));
    }
  }
  return result;
}

bool EntityQueryable::CheckValidAffectsStmtNo(int stmt_no) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  std::unordered_set<std::string> ifs = entity_manager_.GetIfStatements();
  std::unordered_set<std::string> whiles = entity_manager_.GetWhileStatements();
  std::unordered_set<std::string> reads = entity_manager_.GetReadStatements();
  std::unordered_set<std::string> prints = entity_manager_.GetPrintStatements();
  std::unordered_set<std::string> calls = entity_manager_.GetCallStatements();
  if (assigns.find(std::to_string(stmt_no)) != assigns.end()) {
    return true;
  } else if (ifs.find(std::to_string(stmt_no)) != ifs.end()) {
    return true;
  } else if (whiles.find(std::to_string(stmt_no)) != whiles.end()) {
    return true;
  } else if (reads.find(std::to_string(stmt_no)) != reads.end()) {
    return true;
  } else if (prints.find(std::to_string(stmt_no)) != prints.end()) {
    return true;
  } else if (calls.find(std::to_string(stmt_no)) != calls.end()) {
    return true;
  }
  return false;
}

bool EntityQueryable::CheckNotAssignStmtNo(int stmt_no) const {
  std::unordered_set<std::string> assigns =
      entity_manager_.GetAssignStatements();
  if (assigns.find(std::to_string(stmt_no)) != assigns.end()) {
    return false;
  }
  return true;
}
