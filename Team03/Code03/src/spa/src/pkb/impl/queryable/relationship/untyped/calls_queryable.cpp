//
// Created by kohha on 5/11/2022.
//

#include "calls_queryable.h"

CallsQueryable::CallsQueryable(RelationshipManager& relationship_manager_)
    : relationship_manager_(relationship_manager_) {}

/// QueryAllCalls
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> CallsQueryable::QueryAllCalls() const {
  return relationship_manager_.GetCallsProcedures();
}

/// QueryAllCallsBy
/// \return Query all procedures that call any procedure
std::unordered_set<std::string> CallsQueryable::QueryAllCallsBy() const {
  return relationship_manager_.GetCallsByProcedures();
}

/// QueryAllCallsBy
/// \return Query all procedures that call or are called by any procedure
std::unordered_set<std::string> CallsQueryable::QueryAllCallsRelations() const {
  std::unordered_set<std::string> result =
      relationship_manager_.GetCallsProcedures();
  std::unordered_set<std::string> called =
      relationship_manager_.GetCallsByProcedures();
  result.merge(called);
  return result;
}

/// QueryCalls
/// \param identifier
/// \return Gets all procedures that directly call a specified procedure
std::unordered_set<std::string> CallsQueryable::QueryCalls(
    std::string identifier) const {
  return relationship_manager_.GetCallsProcedures(identifier);
}

/// QueryCallsBy
/// \param identifier
/// \return Gets all procedures that are directly called by a specified
/// procedure
std::unordered_set<std::string> CallsQueryable::QueryCallsBy(
    std::string identifier) const {
  return relationship_manager_.GetCallsByProcedures(identifier);
}

/// QueryCallsT
/// \param identifier
/// \return Gets all procedures that directly or indirectly call a specified
/// procedure
std::unordered_set<std::string> CallsQueryable::QueryCallsT(
    std::string identifier) const {
  return relationship_manager_.GetCallsTProcedures(identifier);
}

/// QueryCallsTBy
/// \param identifier
/// \return Gets all procedures that are directly or indirectly called by a
/// specified procedure
std::unordered_set<std::string> CallsQueryable::QueryCallsTBy(
    std::string identifier) const {
  return relationship_manager_.GetCallsTByProcedures(identifier);
}
