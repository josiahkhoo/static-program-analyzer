#include "with.h"

#include <cassert>
#include <utility>

With::With(AttributeReference attRefL, AttributeReference attRefR)
    : attRef_left_(std::move(attRefL)), attRef_right_(std::move(attRefR)) {}

std::unordered_set<std::string> With::Fetch(
    const QueryablePkb& queryable_pkb) const {
  return {};
}

std::unordered_set<std::string> With::FetchPossibleRhs(
    std::string lhs, const QueryablePkb& queryable_pkb) const {
  return {};
}

std::unordered_set<std::string> With::FetchPossibleLhs(
    std::string rhs, const QueryablePkb& queryable_pkb) const {
  return {};
}

QueryOperation::Type With::GetType() const {
  if (attRef_right_.IsAttributeName() && attRef_right_.IsAttributeName()) {
    return DOUBLE_SYNONYM;
  } else if (attRef_right_.IsAttributeName() ||
             attRef_right_.IsAttributeName()) {
    return SINGLE_SYNONYM;
  } else {
    return NO_SYNONYM;
  }
}

Synonym With::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return attRef_left_.GetSynonym();
}

std::pair<Synonym, Synonym> With::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {attRef_left_.GetSynonym(), attRef_right_.GetSynonym()};
}

QueryOperation::IterateSide With::GetIterateSide(
    std::vector<std::vector<std::string>> lhs,
    std::vector<std::vector<std::string>> rhs) const {
  // Iterate over smaller side
  if (lhs.size() > rhs.size()) {
    return RHS;
  }
  return LHS;
}
