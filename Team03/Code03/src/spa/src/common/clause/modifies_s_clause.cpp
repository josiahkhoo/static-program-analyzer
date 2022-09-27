#include "modifies_s_clause.h"

#include <cassert>
#include <utility>

ModifiesSClause::ModifiesSClause(StatementReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> ModifiesSClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsIdentifier()) {
      // E.g. Modifies(a, "x")
      return queryable_pkb.QueryModifiesSBy(
          GetRightHandSide().GetIdentifier(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Modifies(a, _)
      return queryable_pkb.QueryAllModifies(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsLineNumber()) {
      // E.g. Modifies(1, a)
      return queryable_pkb.QueryModifiesS(
          GetLeftHandSide().GetLineNumber(),
          GetRightHandSide().GetSynonym().GetEntityType());
    } else if (GetLeftHandSide().IsWildCard()) {
      // E.g. Modifies(_, a)
      return queryable_pkb.QueryAllModifiesBy(
          GetRightHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetLeftHandSide().IsWildCard() && GetRightHandSide().IsWildCard()) {
    return queryable_pkb.QueryAllModifiesRelations();
  }
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryModifiesS(
        GetLeftHandSide().GetLineNumber(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return {GetRightHandSide().GetIdentifier()};
    }
    return {};
  }
  return {};
}

[[nodiscard]] std::unordered_set<std::string> ModifiesSClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryModifiesS(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> ModifiesSClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryModifiesSBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &ModifiesSClause::GetLeftHandSide() const { return lhs_; }

const Reference &ModifiesSClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> ModifiesSClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Modifies(1, a)
    return queryable_pkb.QueryModifiesS(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  return queryable_pkb.QueryAllModifiesBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> ModifiesSClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
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

bool ModifiesSClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs =
        FetchPossibleRhs(GetLeftHandSide().GetIdentifier(), queryable_pkb);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsIdentifier() &&
             GetRightHandSide().IsWildCard()) {
    return !FetchPossibleRhs(GetLeftHandSide().GetIdentifier(), queryable_pkb)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !FetchPossibleLhs(GetRightHandSide().GetIdentifier(), queryable_pkb)
                .empty();
  }
  // Handle for wildcard wildcard
  return !queryable_pkb.QueryAllModifiesRelations().empty();
}