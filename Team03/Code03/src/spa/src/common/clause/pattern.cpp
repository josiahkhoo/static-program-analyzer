#include "pattern.h"

#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

Pattern::Pattern(Synonym syn, EntityReference entity, Expression expression)
    : entity_(std::move(entity)) {
  syn_ = syn.GetIdentifier();
  // Full Wildcard
  Expression exp = std::move(expression);
  if (exp.to_match.empty()) {
    exp.has_back_wildcard = true;
  }
  expression_ = exp;
}

std::map<std::string, std::unordered_set<std::string>> Pattern::Fetch(
    const QueryablePkb &queryable_pkb) const {
  std::string key = GetSyn();
  std::unordered_set<std::string> results;
  std::map<std::string, std::unordered_set<std::string>> map_of_results;

  if (GetEntity().IsSynonym() || GetEntity().IsWildCard()) {
    results = queryable_pkb.QueryAllPattern(expression_);
  } else if (GetEntity().IsIdentifier()) {
    results =
        queryable_pkb.QueryPattern(GetEntity().GetIdentifier(), expression_);
  }
  map_of_results.insert({key, results});
  return map_of_results;
}

const EntityReference &Pattern::GetEntity() const { return entity_; }

const Expression &Pattern::GetExpression() const { return expression_; }

std::string Pattern::GetSyn() const { return syn_; }
