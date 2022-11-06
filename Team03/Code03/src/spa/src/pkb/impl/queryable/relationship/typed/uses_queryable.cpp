//
// Created by kohha on 5/11/2022.
//

#include "uses_queryable.h"

UsesQueryable::UsesQueryable(RelationshipManager& relationship_manager_,
                             EntityQueryable& entity_queryable_)
    : TypedQueryable(relationship_manager_, entity_queryable_) {}

/// QueryAllUses
/// \param type
/// \return All statements or procedures that uses some Variable
std::unordered_set<std::string> UsesQueryable::QueryAllUses(
    EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetUsingProcedures();
  } else {
    return FindIntersect(relationship_manager_.GetUsingStatements(),
                         entity_queryable_.QueryAll(type));
  }
}

/// QueryAllUsesBy
/// \param type
/// \return All Variables that are used by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> UsesQueryable::QueryAllUsesBy(
    EntityType type) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    result = {};
  } else if (type == EntityType::PROCEDURE) {
    result = relationship_manager_.GetVariablesUsedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    result = relationship_manager_.GetVariablesUsedByStatements();
  } else {
    std::unordered_set<std::string> typed_statements =
        entity_queryable_.QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesUsedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
  }
  return result;
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified statement
std::unordered_set<std::string> UsesQueryable::QueryUsesS(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetVariablesUsedByStatement(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryUsesSBy
/// \param identifier
/// \param type
/// \return Query all statements that use a specified variable
std::unordered_set<std::string> UsesQueryable::QueryUsesSBy(
    std::string identifier, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetStatementsUsingVariable(identifier),
      entity_queryable_.QueryAll(type));
}

/// QueryUsesS
/// \param statement_number
/// \param type
/// \return Query all variables used by a specified procedure
std::unordered_set<std::string> UsesQueryable::QueryUsesP(
    std::string identifier, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetVariablesUsedByProcedure(identifier),
      entity_queryable_.QueryAll(type));
}

/// QueryUsesPBy
/// \param identifier
/// \param type
/// \return Query all procedures that use a specified variable
std::unordered_set<std::string> UsesQueryable::QueryUsesPBy(
    std::string identifier, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetProceduresUsingVariable(identifier),
      entity_queryable_.QueryAll(type));
}