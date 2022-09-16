#include "follows_clause.h"

#include <cassert>
#include <utility>

FollowsClause::FollowsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::map<std::string, std::unordered_set<std::string>> FollowsClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));

  std::string key = Clause::GetSyn();
  std::unordered_set<std::string> results;
  std::map<std::string, std::unordered_set<std::string>> map_of_results;

  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. Follow(a, 1)
      results = queryable_pkb.QueryFollowsBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Follow(a, _)
      results = queryable_pkb.QueryAllFollows(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Follow(1, a)
      results = queryable_pkb.QueryFollows(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Follow(_, a)
      results = queryable_pkb.QueryAllFollowsBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
    if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
      results = queryable_pkb.QueryAllFollowsRelations();
    }
  }
  map_of_results.insert({key, results});
  return map_of_results;
}

const Reference &FollowsClause::GetLeftHandSide() const { return lhs_; }

const Reference &FollowsClause::GetRightHandSide() const { return rhs_; }
