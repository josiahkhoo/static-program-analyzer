#include "modifies_p_clause.h"

#include <cassert>
#include <utility>

ModifiesPClause::ModifiesPClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

std::unordered_set<std::string> ModifiesPClause::Fetch(
    const QueryablePkb &queryable_pkb) const {
  // Both left hand and right hand side cannot be synonyms together.
  assert(!(GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()));
  if (GetLeftHandSide().IsSynonym()) {
    if (GetRightHandSide().IsIdentifier()) {
      // E.g. Modifies(a, "x")
      return queryable_pkb.QueryModifiesPBy(
          GetRightHandSide().GetIdentifier(),
          GetLeftHandSide().GetSynonym().GetEntityType());
    } else if (GetRightHandSide().IsWildCard()) {
      // E.g. Modifies(a, _)
      return queryable_pkb.QueryAllModifies(
          GetLeftHandSide().GetSynonym().GetEntityType());
    }
  }
  if (GetRightHandSide().IsSynonym()) {
    if (GetLeftHandSide().IsIdentifier()) {
      // E.g. Modifies("x", a)
      return queryable_pkb.QueryModifiesP(
          GetLeftHandSide().GetIdentifier(),
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
  // Handle for both idents
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryModifiesP(
        GetLeftHandSide().GetIdentifier(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return {GetRightHandSide().GetIdentifier()};
    }
    return {};
  }
  return {};
}

[[nodiscard]] std::unordered_set<std::string> ModifiesPClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryModifiesP(
      lhs, GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> ModifiesPClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryModifiesPBy(
      rhs, GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &ModifiesPClause::GetLeftHandSide() const { return lhs_; }

const Reference &ModifiesPClause::GetRightHandSide() const { return rhs_; }
