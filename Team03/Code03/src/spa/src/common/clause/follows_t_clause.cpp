#include "follows_t_clause.h"

#include <utility>

FollowsTClause::FollowsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> FollowsTClause::Fetch(
    const QueryablePkb& queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. Follow(a, 1)
      return queryable_pkb.QueryFollowTBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Follow(a, _)
      return queryable_pkb.QueryAllFollow(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Follow(1, a)
      return queryable_pkb.QueryFollowT(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Follow(_, a)
      return queryable_pkb.QueryAllFollowBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  return {};
}

const Reference& FollowsTClause::GetLeftHandSide() const { return lhs_; }

const Reference& FollowsTClause::GetRightHandSide() const { return rhs_; }