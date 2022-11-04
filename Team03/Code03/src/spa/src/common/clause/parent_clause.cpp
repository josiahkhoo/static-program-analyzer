#include "parent_clause.h"

#include <utility>

ParentClause::ParentClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> ParentClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryParentBy(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> ParentClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryParent(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &ParentClause::GetLeftHandSide() const { return lhs_; }

const Reference &ParentClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> ParentClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Parent(1, a)
    return queryable_pkb.QueryParentBy(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Parent(_, a)
  return queryable_pkb.QueryAllParentBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> ParentClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Parent(a, 1)
    return queryable_pkb.QueryParent(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Parent(a, _)
  return queryable_pkb.QueryAllParent(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool ParentClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryParentBy(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryParentBy(GetLeftHandSide().GetLineNumber(),
                               EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryParent(GetRightHandSide().GetLineNumber(),
                             EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllParentsRelations().empty();
}
