#include "uses_p_clause.h"

#include <utility>

UsesPClause::UsesPClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> UsesPClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryUsesP(
      lhs, GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> UsesPClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryUsesPBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &UsesPClause::GetLeftHandSide() const { return lhs_; }

const Reference &UsesPClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> UsesPClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier()) {
    // E.g. Uses("x", a)
    return queryable_pkb.QueryUsesP(
        GetLeftHandSide().GetIdentifier(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Uses(_, a)
  return queryable_pkb.QueryAllUsesBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> UsesPClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Uses(a, "x")
    return queryable_pkb.QueryUsesPBy(
        GetRightHandSide().GetIdentifier(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Uses(a, _)
  return queryable_pkb.QueryAllUses(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool UsesPClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryUsesP(
        GetLeftHandSide().GetIdentifier(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsIdentifier() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryUsesP(GetLeftHandSide().GetIdentifier(),
                            EntityType::VARIABLE)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb
                .QueryUsesPBy(GetRightHandSide().GetIdentifier(),
                              EntityType::PROCEDURE)
                .empty();
  }
  // Handle for wildcard wildcard, which is invalid
  return false;
}
