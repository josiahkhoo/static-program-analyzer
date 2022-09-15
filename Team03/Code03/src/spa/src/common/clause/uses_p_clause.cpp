#include "uses_p_clause.h"

#include <cassert>
#include <utility>

UsesPClause::UsesPClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> UsesPClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsIdentifier()) {
      // E.g. Uses(a, "x")
      return queryable_pkb.QueryUsesPBy(
          GetRightHandSide().GetIdentifier(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Uses(a, _)
      return queryable_pkb.QueryAllUses(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsIdentifier()) {
      // E.g. Uses("x", a)
      return queryable_pkb.QueryUsesP(
          GetLeftHandSide().GetIdentifier(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Uses(_, a)
      return queryable_pkb.QueryAllUsesBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllUsesRelations();
  }
  return {};
}

const Reference &UsesPClause::GetLeftHandSide() const { return lhs_; }

const Reference &UsesPClause::GetRightHandSide() const { return rhs_; }
