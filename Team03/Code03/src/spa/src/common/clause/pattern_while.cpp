#include "pattern_while.h"

#include <cassert>
#include <unordered_set>
#include <utility>

#include "common/queryable_pkb.h"

PatternWhile::PatternWhile(Synonym syn, EntityReference entity)
    : syn_(std::move(syn)), entity_(std::move(entity)) {}

std::unordered_set<std::string> PatternWhile::Fetch(
    QueryablePkb &queryable_pkb) {
  if (GetEntity().IsSynonym() || GetEntity().IsWildCard()) {
    return queryable_pkb.QueryAllWhilePattern();
  } else if (GetEntity().IsIdentifier()) {
    return queryable_pkb.QueryWhilePattern(GetEntity().GetIdentifier());
  }
  assert(false);
  return {};
}

std::unordered_set<std::string> PatternWhile::FetchPossibleRhs(
    std::string lhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryPatternVariablesFromWhile(std::stoi(lhs));
}

std::unordered_set<std::string> PatternWhile::FetchPossibleLhs(
    std::string rhs, QueryablePkb &queryable_pkb) {
  return queryable_pkb.QueryWhilePattern(rhs);
}

const EntityReference &PatternWhile::GetEntity() const { return entity_; }

Synonym PatternWhile::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return syn_;
}

std::pair<Synonym, Synonym> PatternWhile::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {syn_, GetEntity().GetSynonym()};
}

QueryOperation::Type PatternWhile::GetType() const {
  // A pattern can only be a single synonym or double synonym
  if (GetEntity().IsSynonym()) {
    return QueryOperation::DOUBLE_SYNONYM;
  }
  return QueryOperation::SINGLE_SYNONYM;
}

QueryOperation::IterateSide PatternWhile::GetIterateSide(
    std::vector<std::vector<std::string>>,
    std::vector<std::vector<std::string>>) const {
  return QueryOperation::RHS;
}

bool PatternWhile::IsTrue(QueryablePkb &) {
  assert(!"Patterns are never no synonyms, this should not get called");
  return false;
}
