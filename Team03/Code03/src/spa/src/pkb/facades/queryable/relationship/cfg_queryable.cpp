#include "cfg_queryable.h"

CfgQueryable::CfgQueryable(const RelationshipManager &relationship_manager_,
                           const EntityQueryable &entity_queryable_)
    : relationship_manager_(relationship_manager_),
      entity_queryable_(entity_queryable_) {}

/// QueryAllNext
/// \return Query all statements that come next to some statement
std::unordered_set<std::string> CfgQueryable::QueryAllNext(
    EntityType type) const {
  return QueryableUtility::FindIntersect(relationship_manager_.GetAllNext(),
                                         entity_queryable_.QueryAll(type));
}

/// QueryAllPrevious
/// \return Query all statements that come previous to some statement
std::unordered_set<std::string> CfgQueryable::QueryAllPrevious(
    EntityType type) const {
  return QueryableUtility::FindIntersect(relationship_manager_.GetAllPrevious(),
                                         entity_queryable_.QueryAll(type));
}

/// QueryAllNext
/// \return Query all statements that come next or previous to some statement
std::unordered_set<std::string> CfgQueryable::QueryAllNextRelations() const {
  std::unordered_set<std::string> result = relationship_manager_.GetAllNext();
  std::unordered_set<std::string> previous =
      relationship_manager_.GetAllPrevious();
  result.merge(previous);
  return result;
}

/// QueryNext
/// \param statement_number statement
/// \return Query statement(s) that immediately comes next after given statement
std::unordered_set<std::string> CfgQueryable::QueryNext(int statement_number,
                                                        EntityType type) const {
  return QueryableUtility::FindIntersect(
      relationship_manager_.GetNext(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryPrevious
/// \param statement_number statement
/// \return Query statement(s) that immediately comes previous before given
/// statement
std::unordered_set<std::string> CfgQueryable::QueryPrevious(
    int statement_number, EntityType type) const {
  return QueryableUtility::FindIntersect(
      relationship_manager_.GetPrevious(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryNextT
/// \param statement_number statement
/// \return Query statement(s) that comes nextT after given statement
std::unordered_set<std::string> CfgQueryable::QueryNextT(
    int statement_number, EntityType type) const {
  return QueryableUtility::FindIntersect(
      relationship_manager_.GetNextT(statement_number),
      entity_queryable_.QueryAll(type));
}

/// QueryPreviousT
/// \param statement_number statement
/// \return Query statement(s) that comes previousT before given statement
std::unordered_set<std::string> CfgQueryable::QueryPreviousT(
    int statement_number, EntityType type) const {
  return QueryableUtility::FindIntersect(
      relationship_manager_.GetPreviousT(statement_number),
      entity_queryable_.QueryAll(type));
}
