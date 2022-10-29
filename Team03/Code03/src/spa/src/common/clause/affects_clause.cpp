#include "affects_clause.h"

AffectsClause::AffectsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> AffectsClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffectsBy(std::stoi(lhs));
}

[[nodiscard]] std::unordered_set<std::string> AffectsClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAffects(std::stoi(rhs));
}

const Reference &AffectsClause::GetLeftHandSide() const { return lhs_; }

const Reference &AffectsClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> AffectsClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  // Ignore read | print | call | while | if
  if (CheckIfNotAssignStatement(GetRightHandSide())) {
    return {};
  }
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Affects(1, s)
    return queryable_pkb.QueryAffectsBy(GetLeftHandSide().GetLineNumber());
  }
  // E.g. Affects(_, s)
  return queryable_pkb.QueryAllAffectsBy();
}

std::unordered_set<std::string> AffectsClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (CheckIfNotAssignStatement(GetLeftHandSide())) {
    return {};
  }
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Affects(s, 1)
    return queryable_pkb.QueryAffects(GetRightHandSide().GetLineNumber());
  }
  // E.g. Affects(s, _)
  return queryable_pkb.QueryAllAffects();
}

bool AffectsClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs =
        queryable_pkb.QueryAffectsBy(GetLeftHandSide().GetLineNumber());
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb.QueryAffectsBy(GetLeftHandSide().GetLineNumber())
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb.QueryAffects(GetRightHandSide().GetLineNumber())
                .empty();
  }
  return !queryable_pkb.QueryAllAffectsBy().empty();
}

bool AffectsClause::IsValid(const QueryablePkb &queryable_pkb) const {
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

QueryOperation::Speed AffectsClause::GetSpeed() const {
  return QueryOperation::Speed::SLOW;
}

bool AffectsClause::CheckIfNotAssignStatement(const Reference& ref) const {
  return !(ref.IsEntityType(STATEMENT) || ref.IsEntityType(ASSIGN));
}
