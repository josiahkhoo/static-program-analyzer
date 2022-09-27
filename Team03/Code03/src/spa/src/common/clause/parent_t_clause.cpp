#include "parent_t_clause.h"

#include <cassert>
#include <utility>

ParentTClause::ParentTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> ParentTClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));

  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsLineNumber()) {
      // E.g. ParentT(a, 1)
      return queryable_pkb.QueryParentT(
          GetRightHandSide().GetLineNumber(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. ParentT(a, _)
      return queryable_pkb.QueryAllParent(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. ParentT(1, a)
      return queryable_pkb.QueryParentTBy(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. ParentT(_, a)
      return queryable_pkb.QueryAllParentBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllParentsRelations();
  }
  assert(false);
}

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
  return !queryable_pkb.QueryAllParentsRelations().empty();
}
