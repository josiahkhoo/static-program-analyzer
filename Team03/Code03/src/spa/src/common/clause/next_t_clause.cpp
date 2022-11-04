#include "next_t_clause.h"

NextTClause::NextTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> NextTClause::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryNextT(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> NextTClause::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryPreviousT(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &NextTClause::GetLeftHandSide() const { return lhs_; }

const Reference &NextTClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> NextTClause::FetchRhs(
    QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Next*(1, s)
    return queryable_pkb.QueryNextT(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Next*(_, s)
  return queryable_pkb.QueryAllPrevious(PROCEDURE);
}

std::unordered_set<std::string> NextTClause::FetchLhs(
    QueryablePkb &queryable_pkb) {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Next*(s, 1)
    return queryable_pkb.QueryPreviousT(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Next*(s, _)
  return queryable_pkb.QueryAllNext(PROCEDURE);
}

bool NextTClause::IsTrue(QueryablePkb &queryable_pkb) {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryNextT(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryNextT(GetLeftHandSide().GetLineNumber(),
                            EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryPreviousT(GetRightHandSide().GetLineNumber(),
                                EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllNextRelations().empty();
}
