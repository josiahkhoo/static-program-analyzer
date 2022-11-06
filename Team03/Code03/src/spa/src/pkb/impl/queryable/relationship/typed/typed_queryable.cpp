#include "typed_queryable.h"

TypedQueryable::TypedQueryable(RelationshipManager &relationship_manager_,
                               EntityQueryable &entity_queryable_)
    : relationship_manager_(relationship_manager_),
      entity_queryable_(entity_queryable_) {}

/// FindIntersect
/// \param statements Statements from relationship manager
/// \param typed_statements Statements from entity manager
/// \return Statements that are in both sets of statements
std::unordered_set<std::string> TypedQueryable::FindIntersect(
    std::unordered_set<std::string> statements,
    std::unordered_set<std::string> typed_statements) const {
  std::unordered_set<std::string> result;
  for (const std::string &statement : statements) {
    if (typed_statements.find(statement) != typed_statements.end()) {
      result.emplace(statement);
    }
  }
  return result;
}