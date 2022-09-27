#include "follows_t_clause.h"

#include <cassert>
#include <utility>

FollowsTClause::FollowsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> FollowsTClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));

  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. Follow(a, 1)
      return queryable_pkb.QueryFollowsTBy(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Follow(a, _)
      return queryable_pkb.QueryAllFollows(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Follow(1, a)
      return queryable_pkb.QueryFollowsT(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Follow(_, a)
      return queryable_pkb.QueryAllFollowsBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllFollowsRelations();
  }
  assert(false);
}

[[nodiscard]] std::unordered_set<std::string> FollowsTClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryFollowsT(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> FollowsTClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryFollowsTBy(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &FollowsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &FollowsTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> FollowsTClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Follow(1, a)
    return queryable_pkb.QueryFollowsT(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Follow(_, a)
  return queryable_pkb.QueryAllFollowsBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> FollowsTClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Follow(a, 1)
    return queryable_pkb.QueryFollowsTBy(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Follow(a, _)
  return queryable_pkb.QueryAllFollows(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool FollowsTClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().GetLineNumber()) {
    auto possible_rhs = FetchPossibleRhs(
        std::to_string(GetLeftHandSide().GetLineNumber()), queryable_pkb);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !FetchPossibleRhs(std::to_string(GetLeftHandSide().GetLineNumber()),
                             queryable_pkb)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !FetchPossibleLhs(std::to_string(GetRightHandSide().GetLineNumber()),
                             queryable_pkb)
                .empty();
  }
  return !queryable_pkb.QueryAllFollowsRelations().empty();
}