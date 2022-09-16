#include "pattern.h"

#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

Pattern::Pattern(EntityReference entity, Expression expression)
    : entity_(std::move(entity)) {
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
  } else {
    return {};
  }
}

const EntityReference &Pattern::GetEntity() const { return entity_; }

const Expression &Pattern::GetExpression() const { return expression_; }
