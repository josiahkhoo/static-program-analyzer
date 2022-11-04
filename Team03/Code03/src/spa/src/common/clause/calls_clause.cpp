#include "calls_clause.h"

CallsClause::CallsClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> CallsClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryCallsBy(lhs);
}

[[nodiscard]] std::unordered_set<std::string> CallsClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryCalls(rhs);
}

const Reference &CallsClause::GetLeftHandSide() const { return lhs_; }

const Reference &CallsClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> CallsClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier()) {
    // E.g. Calls("first", p)
    return queryable_pkb.QueryCallsBy(GetLeftHandSide().GetIdentifier());
  }
  // E.g. Calls(_, p)
  return queryable_pkb.QueryAllCallsBy();
}

std::unordered_set<std::string> CallsClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Calls(p, "first")
    return queryable_pkb.QueryCalls(GetRightHandSide().GetIdentifier());
  }
  // E.g. Calls(p, _)
  return queryable_pkb.QueryAllCalls();
}

bool CallsClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs =
        queryable_pkb.QueryCalls(GetRightHandSide().GetIdentifier());
    if (possible_rhs.find(GetLeftHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsIdentifier() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryCallsBy(GetLeftHandSide().GetIdentifier())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb.QueryCalls(GetRightHandSide().GetIdentifier())
                .empty();
  }
  // Handle for wildcard wildcard
  return !queryable_pkb.QueryAllCalls().empty();
}
