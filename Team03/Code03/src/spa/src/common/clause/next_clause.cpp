#include "next_clause.h"

NextClause::NextClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

[[nodiscard]] std::unordered_set<std::string> NextClause::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryNext(
      std::stoi(lhs), GetRightHandSide().GetSynonym().GetEntityType());
}

[[nodiscard]] std::unordered_set<std::string> NextClause::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryPrevious(
      std::stoi(rhs), GetLeftHandSide().GetSynonym().GetEntityType());
}

const Reference &NextClause::GetLeftHandSide() const { return lhs_; }

const Reference &NextClause::GetRightHandSide() const { return rhs_; }

std::unordered_set<std::string> NextClause::FetchRhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber()) {
    // E.g. Next(1, s)
    return queryable_pkb.QueryNext(
        GetLeftHandSide().GetLineNumber(),
        GetRightHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Next(_, s)
  return queryable_pkb.QueryAllNext(
      GetRightHandSide().GetSynonym().GetEntityType());
}

std::unordered_set<std::string> NextClause::FetchLhs(
    const QueryablePkb &queryable_pkb) const {
  if (GetRightHandSide().IsLineNumber()) {
    // E.g. Next(s, 1)
    return queryable_pkb.QueryPrevious(
        GetRightHandSide().GetLineNumber(),
        GetLeftHandSide().GetSynonym().GetEntityType());
  }
  // E.g. Next(s, _)
  return queryable_pkb.QueryAllPrevious(
      GetLeftHandSide().GetSynonym().GetEntityType());
}

bool NextClause::IsTrue(const QueryablePkb &queryable_pkb) const {
  if (GetLeftHandSide().IsLineNumber() && GetRightHandSide().IsLineNumber()) {
    auto possible_rhs = queryable_pkb.QueryNext(
        GetLeftHandSide().GetLineNumber(), EntityType::STATEMENT);
    if (possible_rhs.find(std::to_string(GetRightHandSide().GetLineNumber())) !=
        possible_rhs.end()) {
      return true;
    }
    return false;
  } else if (GetLeftHandSide().IsLineNumber() &&
             GetRightHandSide().IsWildCard()) {
    return !queryable_pkb
                .QueryNext(GetLeftHandSide().GetLineNumber(),
                           EntityType::STATEMENT)
                .empty();
  } else if (GetLeftHandSide().IsWildCard() &&
             GetRightHandSide().IsLineNumber()) {
    return !queryable_pkb
                .QueryPrevious(GetRightHandSide().GetLineNumber(),
                               EntityType::STATEMENT)
                .empty();
  }
  return !queryable_pkb.QueryAllNextRelations().empty();
}
