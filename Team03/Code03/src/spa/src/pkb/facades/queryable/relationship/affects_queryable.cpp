#include "affects_queryable.h"

AffectsQueryable::AffectsQueryable(
    const RelationshipManager &relationship_manager_,
    const EntityQueryable &entity_queryable_)
    : relationship_manager_(relationship_manager_),
      entity_queryable_(entity_queryable_) {}

/// QueryAllAffects
/// \return Query all assign statements that affects some other statement
std::unordered_set<std::string> AffectsQueryable::QueryAllAffects() const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  return relationship_manager_.GetAllAffects(assigns, calls, reads);
}

/// QueryAllAffectsBy
/// \return Query all assign statements that are affected by some other
/// statement
std::unordered_set<std::string> AffectsQueryable::QueryAllAffectsBy() const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  return relationship_manager_.GetAllAffectsBy(assigns, calls, reads);
}

/// QueryAffects
/// \param statement_number statement
/// \return Query all assign statements that affects given statement
std::unordered_set<std::string> AffectsQueryable::QueryAffects(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  if (entity_queryable_.CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffects(assigns, calls, reads,
                                          statement_number);
}

/// QueryAffectsBy
/// \param statement_number statement
/// \return Query all assign statements that are affected by given statement
std::unordered_set<std::string> AffectsQueryable::QueryAffectsBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  if (entity_queryable_.CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsBy(assigns, calls, reads,
                                            statement_number);
}

/// QueryAffectsT
/// \param statement_number statement
/// \return Query all assign statements that affectsT given statement
std::unordered_set<std::string> AffectsQueryable::QueryAffectsT(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  if (entity_queryable_.CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsT(assigns, calls, reads,
                                           statement_number);
}

/// QueryAffectsTBy
/// \param statement_number statement
/// \return Query all assign statements that are affectedT by given statement
std::unordered_set<std::string> AffectsQueryable::QueryAffectsTBy(
    int statement_number) const {
  std::unordered_set<std::string> assigns =
      entity_queryable_.GetAssignStatements();
  std::unordered_set<std::string> calls = entity_queryable_.GetCallStatements();
  std::unordered_set<std::string> reads = entity_queryable_.GetReadStatements();
  if (entity_queryable_.CheckNotAssignStmtNo(statement_number)) {
    return {};
  }
  return relationship_manager_.GetAffectsTBy(assigns, calls, reads,
                                             statement_number);
}