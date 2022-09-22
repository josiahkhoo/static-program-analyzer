#include "calls_t_clause.h"

#include <cassert>

CallsTClause::CallsTClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> CallsTClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsIdentifier()) {
      // E.g. Calls*(p, "first")
      return queryable_pkb.QueryCallsTBy(
          GetRightHandSide().GetIdentifier(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Calls*(p, _)
      return queryable_pkb.QueryAllCalls(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsIdentifier()) {
      // E.g. Calls*("first", p)
      return queryable_pkb.QueryCallsT(
          GetLeftHandSide().GetIdentifier(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Calls*(_, p)
      return queryable_pkb.QueryAllCallsBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllCallsRelations();
  }
  // Handle for both idents
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryCallsT(
        GetLeftHandSide().GetIdentifier(), EntityType::PROCEDURE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return {GetRightHandSide().GetIdentifier()};
    }
    return {};
  }
  return {};
}

[[nodiscard]] std::unordered_set<std::string> CallsTClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryCallsT(
      lhs, GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> CallsTClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryCallsTBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &CallsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &CallsTClause::GetRightHandSide() const { return rhs_; }
