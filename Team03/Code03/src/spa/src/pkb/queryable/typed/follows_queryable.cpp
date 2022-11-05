//
// Created by kohha on 5/11/2022.
//

#include "follows_queryable.h"

FollowsQueryable::FollowsQueryable(RelationshipManager& relationship_manager_,
                                   EntityQueryable& entity_queryable_)
    : TypedQueryable(relationship_manager_,
                                       entity_queryable_) {}

/// QueryAllFollows
/// \param type
/// \return Query all statements following any statement of a specified type
std::unordered_set<std::string> FollowsQueryable::QueryAllFollows(
    EntityType type) const {
  return FindIntersect(relationship_manager_.GetFollowsStatements(),
                       entity_queryable_.QueryAll(type));
}

/// QueryAllFollowsBy
/// \param type
/// \return Query all statements followed by any statement of a specified type
std::unordered_set<std::string> FollowsQueryable::QueryAllFollowsBy(
    EntityType type) const {
  return FindIntersect(relationship_manager_.GetFollowsByStatements(),
                       entity_queryable_.QueryAll(type));
}

/// QueryAllFollows
/// \param type
/// \return Gets all statements following or followed by any statement
std::unordered_set<std::string> FollowsQueryable::QueryAllFollowsRelations()
    const {
  return relationship_manager_.GetFollowsStatements();
}

/// QueryFollows
/// \param statement_number
/// \param type
/// \return Query all statements directly following a specified
/// statement
std::unordered_set<std::string> FollowsQueryable::QueryFollows(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryFollowsBy
/// \param statement_number
/// \param type
/// \return Query all statements directly followed by a specified
/// statement
std::unordered_set<std::string> FollowsQueryable::QueryFollowsBy(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsByStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryFollowsT
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly following a specified
/// statement
std::unordered_set<std::string> FollowsQueryable::QueryFollowsT(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsTStatements(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryFollowsTBy
/// \param statement_number
/// \param type
/// \return Query all statements directly or indirectly followed by a specified
/// statement
std::unordered_set<std::string> FollowsQueryable::QueryFollowsTBy(
    int statement_number, EntityType type) const {
  return FindIntersect(
      relationship_manager_.GetFollowsTByStatements(statement_number),
      entity_queryable_.QueryAll(type));
}
