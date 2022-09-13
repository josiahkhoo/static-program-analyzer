#include "follows_clause.h"

#include <cassert>
#include <utility>

FollowsClause::FollowsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> FollowsClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. Follow(a, 1)
      return queryable_pkb.QueryFollowsBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Follow(a, _)
      return queryable_pkb.QueryAllFollows(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Follow(1, a)
      return queryable_pkb.QueryFollows(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Follow(_, a)
      return queryable_pkb.QueryAllFollowsBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
    if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
      return queryable_pkb.QueryAllFollowsRelations();
    }
  }
  return {};
}

const Reference &FollowsClause::GetLeftHandSide() const { return lhs_; }

const Reference &FollowsClause::GetRightHandSide() const { return rhs_; }
