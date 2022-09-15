#include "parent_t_clause.h"

#include <cassert>
#include <utility>

ParentTClause::ParentTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::map<std::string, std::unordered_set<std::string>> ParentTClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));

  std::string key = Clause::GetSyn();
  std::unordered_set<std::string> results;
  std::map<std::string, std::unordered_set<std::string>> map_of_results;

  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. ParentT(a, 1)
      results = queryable_pkb.QueryParentTBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. ParentT(a, _)
      results = queryable_pkb.QueryAllParent(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. ParentT(1, a)
      results = queryable_pkb.QueryParentT(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. ParentT(_, a)
      results = queryable_pkb.QueryAllParentBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsWildCard()) {
    results = queryable_pkb.QueryAllParentsRelations();
  }
  map_of_results.insert({key, results});
  return map_of_results;
}

const Reference &ParentTClause::GetLeftHandSide() const { return lhs_; }

const Reference &ParentTClause::GetRightHandSide() const { return rhs_; }
