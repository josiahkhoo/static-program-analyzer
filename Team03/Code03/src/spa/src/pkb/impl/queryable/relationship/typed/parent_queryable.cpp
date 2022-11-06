//
// Created by kohha on 5/11/2022.
//

#include "parent_queryable.h"

ParentQueryable::ParentQueryable(RelationshipManager& relationship_manager_,
                                 EntityQueryable& entity_queryable_)
    : TypedQueryable(relationship_manager_, entity_queryable_) {}

/// QueryAllParent
/// \return Query all statements that are direct parents of any statement
std::unordered_set<std::string> ParentQueryable::QueryAllParent(
    EntityType type) const {
  return FindIntersect(relationship_manager_.GetParentStatements(),
                       entity_queryable_.QueryAll(type));
}

/// QueryAllParentBy
/// \return Query all statements that are direct children of any statement
std::unordered_set<std::string> ParentQueryable::QueryAllParentBy(
    EntityType type) const {
  return FindIntersect(relationship_manager_.GetParentByStatements(),
                       entity_queryable_.QueryAll(type));
}

/// QueryAllParentsRelations
/// \return Query all parent and children statements of any statement
std::unordered_set<std::string> ParentQueryable::QueryAllParentsRelations()
    const {
  std::unordered_set<std::string> res =
      relationship_manager_.GetParentStatements();
  std::unordered_set<std::string> children =
      relationship_manager_.GetParentByStatements();
  res.merge(children);
  return res;
}

/// QueryParent
/// \param statement_number
/// \param type
/// \return Query all statements that are direct parents of a specified
/// statement
std::unordered_set<std::string> ParentQueryable::QueryParent(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryParentBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct children of a specified
/// statement
std::unordered_set<std::string> ParentQueryable::QueryParentBy(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentByStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryParentT
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect parents of a
/// specified statement
std::unordered_set<std::string> ParentQueryable::QueryParentT(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentTStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryParentTBy
/// \param statement_number
/// \param type
/// \return Query all statements that are direct or indirect children of a
/// specified statement
std::unordered_set<std::string> ParentQueryable::QueryParentTBy(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetParentTByStatements(statement_number),
      entity_queryable_.QueryAll(type));
}