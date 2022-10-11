#include "affects_t_clause.h"

AffectsTClause::AffectsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> AffectsTClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffectsT(std::stoi(lhs));
}

[[nodiscard]] std::unordered_set<std::string> AffectsTClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffectsTBy(std::stoi(rhs));
}

const Reference &AffectsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &AffectsTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> AffectsTClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Affects*(1, s)
    return queryable_pkb.QueryAffectsT(GetLeftHandSide().GetLineNumber());
  }
  // E.g. Affects*(_, s)
  return queryable_pkb.QueryAllAffectsBy();
}

std::unordered_set<std::string> AffectsTClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Affects*(s, 1)
    return queryable_pkb.QueryAffectsTBy(GetRightHandSide().GetLineNumber());
  }
  // E.g. Affects*(s, _)
  return queryable_pkb.QueryAllAffects();
}

bool AffectsTClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().GetLineNumber()) {
    auto possible_rhs =
        queryable_pkb.QueryAffectsT(GetLeftHandSide().GetLineNumber());
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryAffectsT(GetLeftHandSide().GetLineNumber())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb.QueryAffectsTBy(GetRightHandSide().GetLineNumber())
                .empty();
  }
  return !queryable_pkb.QueryAllAffects().empty();
}
