#include "uses_s_clause.h"

#include <utility>

UsesSClause::UsesSClause(StatementReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> UsesSClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryUsesS(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> UsesSClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryUsesSBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &UsesSClause::GetLeftHandSide() const { return lhs_; }

const Reference &UsesSClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> UsesSClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Uses(1, a)
    return queryable_pkb.QueryUsesS(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Uses(_, a)
  return queryable_pkb.QueryAllUsesBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> UsesSClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Uses(a, "x")
    return queryable_pkb.QueryUsesSBy(
        GetRightHandSide().GetIdentifier(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Uses(a, _)
  return queryable_pkb.QueryAllUses(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool UsesSClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryUsesS(
        GetLeftHandSide().GetLineNumber(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryUsesS(GetLeftHandSide().GetLineNumber(),
                            EntityType::VARIABLE)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb
                .QueryUsesSBy(GetRightHandSide().GetIdentifier(),
                              EntityType::STATEMENT)
                .empty();
  }
  // Handle for wildcard wildcard, which is invalid
  return false;
}
