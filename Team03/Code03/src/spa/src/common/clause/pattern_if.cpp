#include "pattern_if.h"

#include <cassert>
#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

PatternIf::PatternIf(Synonym syn, EntityReference entity)
    : syn_(std::move(syn)), entity_(std::move(entity)) {}

std::unordered_set<std::string> PatternIf::Fetch(QueryablePkb &queryable_pkb) {
  if (GetEntity().IsSynonym() || GetEntity().IsWildCard()) {
    return queryable_pkb.QueryAllIfPattern();
  } else if (GetEntity().IsIdentifier()) {
    return queryable_pkb.QueryIfPattern(GetEntity().GetIdentifier());
  }
  assert(false);
  return {};
}

std::unordered_set<std::string> PatternIf::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryPatternVariablesFromIf(std::stoi(lhs));
}

std::unordered_set<std::string> PatternIf::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryIfPattern(rhs);
}

const EntityReference &PatternIf::GetEntity() const { return entity_; }

Synonym PatternIf::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return syn_;
}

std::pair<Synonym, Synonym> PatternIf::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {syn_, GetEntity().GetSynonym()};
}

QueryOperation::Type PatternIf::GetType() const {
  // A pattern can only be a single synonym or double synonym
  if (GetEntity().IsSynonym()) {
    return QueryOperation::DOUBLE_SYNONYM;
  }
  return QueryOperation::SINGLE_SYNONYM;
}

QueryOperation::IterateSide PatternIf::GetIterateSide(
    std::vector<std::vector<std::string>>,
    std::vector<std::vector<std::string>>) const {
  return QueryOperation::RHS;
}

bool PatternIf::IsTrue(QueryablePkb &) {
  assert(!"Patterns are never no synonyms, this should not get called");
  return false;
}
