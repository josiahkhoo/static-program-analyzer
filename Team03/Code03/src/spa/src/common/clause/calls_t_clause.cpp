#include "calls_t_clause.h"

CallsTClause::CallsTClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> CallsTClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryCallsTBy(lhs);
}

[[nodiscard]] std::unordered_set<std::string> CallsTClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryCallsT(rhs);
}

const Reference &CallsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &CallsTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> CallsTClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier()) {
    // E.g. Calls*("first", p)
    return queryable_pkb.QueryCallsTBy(GetLeftHandSide().GetIdentifier());
  }
  // E.g. Calls*(_, p)
  return queryable_pkb.QueryAllCallsBy();
}

std::unordered_set<std::string> CallsTClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Calls*(p, "first")
    return queryable_pkb.QueryCallsT(GetRightHandSide().GetIdentifier());
  }
  // E.g. Calls*(p, _)
  return queryable_pkb.QueryAllCalls();
}

bool CallsTClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs =
        queryable_pkb.QueryCallsT(GetRightHandSide().GetIdentifier());
    if (possible_rhs.find(GetLeftHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsIdentifier() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryCallsTBy(GetLeftHandSide().GetIdentifier())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb.QueryCallsT(GetRightHandSide().GetIdentifier())
                .empty();
  }
  // Handle for wildcard wildcard
  return !queryable_pkb.QueryAllCalls().empty();
}