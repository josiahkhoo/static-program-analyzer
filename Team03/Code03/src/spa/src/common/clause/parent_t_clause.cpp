#include "parent_t_clause.h"

#include <utility>

ParentTClause::ParentTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}


[[nodiscard]] std::unordered_set<std::string> ParentTClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryParentTBy(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> ParentTClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryParentT(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &ParentTClause::GetLeftHandSide() const { return lhs_; }

const Reference &ParentTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> ParentTClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Parent(1, a)
    return queryable_pkb.QueryParentTBy(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Parent(_, a)
  return queryable_pkb.QueryAllParentBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> ParentTClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Parent(a, 1)
    return queryable_pkb.QueryParentT(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Parent(a, _)
  return queryable_pkb.QueryAllParent(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool ParentTClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().GetLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryParentTBy(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryParentTBy(GetLeftHandSide().GetLineNumber(),
                                EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryParentT(GetRightHandSide().GetLineNumber(),
                              EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllParentsRelations().empty();
}
