#include "modifies_p_clause.h"

#include <utility>

ModifiesPClause::ModifiesPClause(EntityReference lhs, EntityReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

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

std::unordered_set<std::string> ModifiesPClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsIdentifier()) {
    // E.g. Modifies("x", a)
    return queryable_pkb.QueryModifiesP(
        GetLeftHandSide().GetIdentifier(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  return queryable_pkb.QueryAllModifiesBy(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> ModifiesPClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsIdentifier()) {
    // E.g. Modifies(a, "x")
    return queryable_pkb.QueryModifiesPBy(
        GetRightHandSide().GetIdentifier(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Modifies(a, _)
  return queryable_pkb.QueryAllModifies(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool ModifiesPClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsIdentifier() && GetRightHandSide().IsIdentifier()) {
    auto possible_rhs = queryable_pkb.QueryModifiesP(
        GetLeftHandSide().GetIdentifier(), EntityType::VARIABLE);
    if (possible_rhs.find(GetRightHandSide().GetIdentifier()) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsIdentifier() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryModifiesP(GetLeftHandSide().GetIdentifier(),
                                EntityType::VARIABLE)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsIdentifier()) {
    return !queryable_pkb
                .QueryModifiesPBy(GetRightHandSide().GetIdentifier(),
                                  EntityType::PROCEDURE)
                .empty();
  }
  // Handle for wildcard wildcard
  return !queryable_pkb.QueryAllModifiesRelations().empty();
}
