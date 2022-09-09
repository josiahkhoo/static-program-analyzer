#include "parent_t_clause.h"

#include <cassert>
#include <utility>

ParentTClause::ParentTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> ParentTClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. ParentT(a, 1)
      return queryable_pkb.QueryParentTBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. ParentT(a, _)
      return queryable_pkb.QueryAllParent(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. ParentT(1, a)
      return queryable_pkb.QueryParentT(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. ParentT(_, a)
      return queryable_pkb.QueryAllParentBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  return {};
}

const Reference &ParentTClause::GetLeftHandSide() const { return lhs_; }

const Reference &ParentTClause::GetRightHandSide() const { return rhs_; }
