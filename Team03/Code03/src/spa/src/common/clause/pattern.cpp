#include "pattern.h"

#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

Pattern::Pattern(EntityReference entity, Expression expression)
    : entity_(std::move(entity)), expression_(std::move(expression)) {}

std::unordered_set<std::string> Pattern::Fetch(
    const QueryablePkb &queryable_pkb) const {
  Expression q_exp = expression_;
  // Full Wildcard
  if (expression_.to_match.empty()) {
    Expression wild_expression;
    wild_expression.has_front_wildcard = true;
    wild_expression.has_back_wildcard = true;
    q_exp = wild_expression;
  }
  if (GetEntity().IsSynonym()) {
    return queryable_pkb.QueryAllPattern(q_exp);
  } else if (GetEntity().IsIdentifier()) {
    return queryable_pkb.QueryPattern(GetEntity().GetIdentifier(), q_exp);
  } else if (GetEntity().IsWildCard()) {
    return queryable_pkb.QueryAllPattern(q_exp);
  } else {
    return {};
  }
}

const EntityReference &Pattern::GetEntity() const { return entity_; }

const Expression &Pattern::GetExpression() const { return expression_; }
