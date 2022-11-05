#include "follows_t_clause.h"

#include <utility>

FollowsTClause::FollowsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> FollowsTClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryFollowsT(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> FollowsTClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryFollowsTBy(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &FollowsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &FollowsTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> FollowsTClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
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
    QueryablePkb &queryable_pkb) {
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

bool FollowsTClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryFollowsT(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryFollowsT(GetLeftHandSide().GetLineNumber(),
                               EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryFollowsTBy(GetRightHandSide().GetLineNumber(),
                                 EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllFollowsRelations().empty();
}