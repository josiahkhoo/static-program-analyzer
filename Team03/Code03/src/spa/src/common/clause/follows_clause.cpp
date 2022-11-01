#include "follows_clause.h"

#include <utility>

FollowsClause::FollowsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> FollowsClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryFollows(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> FollowsClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryFollowsBy(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &FollowsClause::GetLeftHandSide() const { return lhs_; }

const Reference &FollowsClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> FollowsClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Follow(1, a)
    return queryable_pkb.QueryFollows(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Follow(_, a)
  return queryable_pkb.QueryAllFollowsBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> FollowsClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Follow(a, 1)
    return queryable_pkb.QueryFollowsBy(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Follow(a, _)
  return queryable_pkb.QueryAllFollows(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool FollowsClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryFollows(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryFollows(GetLeftHandSide().GetLineNumber(),
                              EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryFollowsBy(GetRightHandSide().GetLineNumber(),
                                EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllFollowsRelations().empty();
}
