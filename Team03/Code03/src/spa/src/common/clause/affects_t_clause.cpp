#include "affects_t_clause.h"

AffectsTClause::AffectsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> AffectsTClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryAffectsTBy(std::stoi(lhs));
}

[[nodiscard]] std::unordered_set<std::string> AffectsTClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryAffectsT(std::stoi(rhs));
}

const Reference &AffectsTClause::GetLeftHandSide() const { return lhs_; }

const Reference &AffectsTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> AffectsTClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  // Ignore read | print | call | while | if
  if (CheckIfNotAssignStatement(GetRightHandSide())) {
    return {};
  }
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Affects*(1, s)
    return queryable_pkb.QueryAffectsTBy(GetLeftHandSide().GetLineNumber());
  }
  // E.g. Affects*(_, s)
  return queryable_pkb.QueryAllAffectsBy();
}

std::unordered_set<std::string> AffectsTClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (CheckIfNotAssignStatement(GetLeftHandSide())) {
    return {};
  }
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Affects*(s, 1)
    return queryable_pkb.QueryAffectsT(GetRightHandSide().GetLineNumber());
  }
  // E.g. Affects*(s, _)
  return queryable_pkb.QueryAllAffects();
}

bool AffectsTClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs =
        queryable_pkb.QueryAffectsTBy(GetLeftHandSide().GetLineNumber());
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryAffectsTBy(GetLeftHandSide().GetLineNumber())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb.QueryAffectsT(GetRightHandSide().GetLineNumber())
                .empty();
  }
  return !queryable_pkb.QueryAllAffectsBy().empty();
}

bool AffectsTClause::IsValid(const QueryablePkb &queryable_pkb) const {
  int line_no;
  if (GetLeftHandSide().IsLineNumber()) {
    line_no = GetLeftHandSide().GetLineNumber();
  } else if (GetRightHandSide().IsLineNumber()) {
    line_no = GetRightHandSide().IsLineNumber();
  } else {
    return true;
  }
  return queryable_pkb.CheckValidAffectsStmtNo(line_no);
}

QueryOperation::Speed AffectsTClause::GetSpeed() const {
  return QueryOperation::Speed::SLOWEST;
}

bool AffectsTClause::CheckIfNotAssignStatement(const Reference &ref) const {
  return !(ref.IsEntityType(STATEMENT) || ref.IsEntityType(ASSIGN));
}
