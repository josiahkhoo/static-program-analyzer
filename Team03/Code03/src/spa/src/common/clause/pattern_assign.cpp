#include "pattern_assign.h"

#include <cassert>
#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

PatternAssign::PatternAssign(Synonym syn, EntityReference entity,
                             Expression expression)
    : syn_(std::move(syn)), entity_(std::move(entity)) {
  // Full Wildcard
  Expression exp = std::move(expression);
  if (exp.to_match.empty()) {
    exp.has_back_wildcard = true;
  }
  expression_ = exp;
}

std::unordered_set<std::string> PatternAssign::Fetch(
    const QueryablePkb &queryable_pkb) const {
  if (GetEntity().IsSynonym() || GetEntity().IsWildCard()) {
    return queryable_pkb.QueryAllAssignPattern(expression_);
  } else if (GetEntity().IsIdentifier()) {
    return queryable_pkb.QueryAssignPattern(GetEntity().GetIdentifier(),
                                            expression_);
  }
  assert(false);
  return {};
}

std::unordered_set<std::string> PatternAssign::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryPatternVariablesFromAssign(std::stoi(lhs));
}

std::unordered_set<std::string> PatternAssign::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryAssignPattern(rhs, expression_);
}

const EntityReference &PatternAssign::GetEntity() const { return entity_; }

const Expression &PatternAssign::GetExpression() const { return expression_; }

Synonym PatternAssign::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return syn_;
}

std::pair<Synonym, Synonym> PatternAssign::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {syn_, GetEntity().GetSynonym()};
}

QueryOperation::Type PatternAssign::GetType() const {
  // A pattern can only be a single synonym or double synonym
  if (GetEntity().IsSynonym()) {
    return QueryOperation::DOUBLE_SYNONYM;
  }
  return QueryOperation::SINGLE_SYNONYM;
}

QueryOperation::IterateSide PatternAssign::GetIterateSide(
    std::vector<std::vector<std::string>>,
    std::vector<std::vector<std::string>>) const {
  return QueryOperation::RHS;
}

bool PatternAssign::IsTrue(const QueryablePkb &) const {
  assert(!"Patterns are never no synonyms, this should not get called");
  return false;
}
