#include "pattern.h"

#include <cassert>
#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

Pattern::Pattern(Synonym syn, EntityReference entity, Expression expression)
    : syn_(std::move(syn)), entity_(std::move(entity)) {
  // Full Wildcard
  Expression exp = std::move(expression);
  if (exp.to_match.empty()) {
    exp.has_back_wildcard = true;
  }
  expression_ = exp;
}

std::unordered_set<std::string> Pattern::Fetch(
    const QueryablePkb &queryable_pkb) const {
  if (GetEntity().IsSynonym() || GetEntity().IsWildCard()) {
    return queryable_pkb.QueryAllPattern(expression_);
  } else if (GetEntity().IsIdentifier()) {
    return queryable_pkb.QueryPattern(GetEntity().GetIdentifier(), expression_);
  }
  assert(false);
}

std::unordered_set<std::string> Pattern::FetchPossibleRhs(
    std::string lhs, const QueryablePkb &queryable_pkb) const {
  assert(false);
  return {};
}

std::unordered_set<std::string> Pattern::FetchPossibleLhs(
    std::string rhs, const QueryablePkb &queryable_pkb) const {
  return queryable_pkb.QueryPattern(rhs, expression_);
  assert(false);
}

const EntityReference &Pattern::GetEntity() const { return entity_; }

const Expression &Pattern::GetExpression() const { return expression_; }

Synonym Pattern::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return syn_;
}

std::pair<Synonym, Synonym> Pattern::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {syn_, GetEntity().GetSynonym()};
}

QueryOperation::Type Pattern::GetType() const {
  // A pattern can only be a single synonym or double synonym
  if (GetEntity().IsSynonym()) {
    return QueryOperation::DOUBLE_SYNONYM;
  }
  return QueryOperation::SINGLE_SYNONYM;
}

QueryOperation::IterateSide Pattern::GetIterateSide(
    std::vector<std::vector<std::string>> lhs,
    std::vector<std::vector<std::string>> rhs) const {
  return QueryOperation::RHS;
}
