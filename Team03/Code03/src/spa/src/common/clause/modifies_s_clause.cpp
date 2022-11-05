#include "modifies_s_clause.h"

#include <utility>

ModifiesSClause::ModifiesSClause(StatementReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> ModifiesSClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryModifiesS(std::stoi(lhs));
}

[[nodiscard]] std::unordered_set<std::string> ModifiesSClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryModifiesSBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &ModifiesSClause::GetLeftHandSide() const { return lhs_; }

const Reference &ModifiesSClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> ModifiesSClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Modifies(1, a)
    return queryable_pkb.QueryModifiesS(GetLeftHandSide().GetLineNumber());
  }
  return queryable_pkb.QueryAllModifiesBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> ModifiesSClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Modifies(a, "x")
    return queryable_pkb.QueryModifiesSBy(
        GetRightHandSide().GetIdentifier(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Modifies(a, _)
  return queryable_pkb.QueryAllModifies(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool ModifiesSClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs =
        queryable_pkb.QueryModifiesS(GetLeftHandSide().GetLineNumber());
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryModifiesS(GetLeftHandSide().GetLineNumber())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb
                .QueryModifiesSBy(GetRightHandSide().GetIdentifier(),
                                  EntityType::STATEMENT)
                .empty();
  }
  // Handle for wildcard wildcard, which is invalid
  return false;
}
