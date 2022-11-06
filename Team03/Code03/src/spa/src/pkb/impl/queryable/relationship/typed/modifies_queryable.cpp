//
// Created by kohha on 5/11/2022.
//

#include "modifies_queryable.h"

ModifiesQueryable::ModifiesQueryable(RelationshipManager& relationship_manager_,
                                     EntityQueryable& entity_queryable_)
    : TypedQueryable(relationship_manager_, entity_queryable_) {}

/// QueryAllModifies
/// \param type
/// \return All statements or procedures that modifies some Variable
std::unordered_set<std::string> ModifiesQueryable::QueryAllModifies(
    EntityType type) const {
  if (type == EntityType::PROCEDURE) {
    return relationship_manager_.GetModifyingProcedures();
  } else {
    return FindIntersect(relationship_manager_.GetModifyingStatements(),
                         entity_queryable_.QueryAll(type));
  }
}

/// QueryAllModifiesBy
/// \param type
/// \return All Variables that are modified by EntityType (Procedure or
/// Statement types)
std::unordered_set<std::string> ModifiesQueryable::QueryAllModifiesBy(
    EntityType type) const {
  std::unordered_set<std::string> result;
  if (type == EntityType::CONSTANT || type == EntityType::VARIABLE) {
    result = {};
  } else if (type == EntityType::PROCEDURE) {
    result = relationship_manager_.GetVariablesModifiedByProcedures();
  } else if (type == EntityType::STATEMENT) {
    result = relationship_manager_.GetVariablesModifiedByStatements();
  } else {
    std::unordered_set<std::string> typed_statements =
        entity_queryable_.QueryAll(type);
    for (const std::string& statement : typed_statements) {
      std::unordered_set<std::string> vars =
          relationship_manager_.GetVariablesModifiedByStatement(
              std::stoi(statement));
      for (const std::string& var : vars) {
        result.emplace(var);
      }
    }
  }
  return result;
}

/// QueryModifiesS
/// \param statement_number
/// \return Variables modified in given statement_number
std::unordered_set<std::string> ModifiesQueryable::QueryModifiesS(
    int statement_number) const {
  return relationship_manager_.GetVariablesModifiedByStatement(
      statement_number);
}

/// QueryModifiesSBy
/// \param identifier
/// \param type
/// \return Statements that modifies given Variable identifier
std::unordered_set<std::string> ModifiesQueryable::QueryModifiesSBy(
    std::string identifier, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetStatementsModifyingVariable(identifier),
      entity_queryable_.QueryAll(type));
}

/// QueryModifiesP
/// \param identifier
/// \return Variables modified in given Procedure identifier
std::unordered_set<std::string> ModifiesQueryable::QueryModifiesP(
    std::string identifier) const {
  return relationship_manager_.GetVariablesModifiedByProcedure(identifier);
}

/// QueryModifiesPBy
/// \param identifier
/// \return Procedures that modifies given Variable identifier
std::unordered_set<std::string> ModifiesQueryable::QueryModifiesPBy(
    std::string identifier) const {
  return relationship_manager_.GetProceduresModifyingVariable(identifier);
}