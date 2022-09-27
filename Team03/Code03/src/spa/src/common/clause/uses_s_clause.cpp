#include "uses_s_clause.h"

#include <cassert>
#include <utility>

UsesSClause::UsesSClause(StatementReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> UsesSClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsIdentifier()) {
      // E.g. Uses(a, "x")
      return queryable_pkb.QueryUsesSBy(
          GetRightHandSide().GetIdentifier(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Uses(a, _)
      return queryable_pkb.QueryAllUses(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Uses(1, a)
      return queryable_pkb.QueryUsesS(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Uses(_, a)
      return queryable_pkb.QueryAllUsesBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllUsesRelations();
  }
  // Handle for one line number, one idents
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryUsesS(
        GetLeftHandSide().GetLineNumber(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return {GetRightHandSide().GetIdentifier()};
    }
    return {};
  }
  return {};
}

[[nodiscard]] std::unordered_set<std::string> UsesSClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryUsesS(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> UsesSClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryUsesSBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &UsesSClause::GetLeftHandSide() const { return lhs_; }

const Reference &UsesSClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> UsesSClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
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
    const QueryablePkb &queryable_pkb) const {
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

bool UsesSClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = FetchPossibleRhs(
        std::to_string(GetLeftHandSide().GetLineNumber()), queryable_pkb);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
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
             GetRightHandSide().IsIdentifier()) {
    return !FetchPossibleLhs(GetRightHandSide().GetIdentifier(), queryable_pkb)
                .empty();
  }
  // Handle for wildcard wildcard
  return !queryable_pkb.QueryAllUsesRelations().empty();
}
