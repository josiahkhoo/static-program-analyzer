#include "affects_clause.h"

AffectsClause::AffectsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> AffectsClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffects(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> AffectsClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffectsBy(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &AffectsClause::GetLeftHandSide() const { return lhs_; }

const Reference &AffectsClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> AffectsClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Affects(1, s)
    return queryable_pkb.QueryAffects(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Affects(_, s)
  return queryable_pkb.QueryAllAffectsBy();
}

std::unordered_set<std::string> AffectsClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Affects(s, 1)
    return queryable_pkb.QueryAffectsBy(GetRightHandSide().GetLineNumber(),
                                        EntityType::STATEMENT);
  }
  // E.g. Affects(s, _)
  return queryable_pkb.QueryAllAffects();
}

bool AffectsClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().GetLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryAffects(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryAffects(GetLeftHandSide().GetLineNumber(),
                              EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryAffectsBy(GetRightHandSide().GetLineNumber(),
                                EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllAffectsRelations().empty();
}
