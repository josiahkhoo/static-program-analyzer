#include "with.h"

#include <cassert>
#include <utility>

With::With(AttributeReference attRefL, AttributeReference attRefR)
    : lhs_(std::move(attRefL)), rhs_(std::move(attRefR)) {}

std::unordered_set<std::string> With::Fetch(
    const QueryablePkb& queryable_pkb) const {
  if (GetType() == NO_SYNONYM) {
    // E.g. with "x" = 1
    // Returns 1 or 0 if matches
    bool res = lhs_.GetValue() == rhs_.GetValue();
    return {std::to_string(res)};
  } else if (GetType() == DOUBLE_SYNONYM) {
    // E.g. with x.procName = y.procName
    return queryable_pkb.QueryWithAttribute(
        lhs_.GetSynonym().GetEntityType(), lhs_.GetAttributeName(),
        rhs_.GetSynonym().GetEntityType(), rhs_.GetAttributeName());
  } else if (lhs_.IsAttributeName()) {
    if (rhs_.IsIdentifier()) {
      // E.g. with x.procName = "name"
      return queryable_pkb.QueryWithAttribute(lhs_.GetSynonym().GetEntityType(),
                                              lhs_.GetAttributeName(),
                                              rhs_.GetIdentifier());
    } else if (rhs_.IsLineNumber()) {
      // E.g. with x.stmt# = 1
      return queryable_pkb.QueryWithAttribute(lhs_.GetSynonym().GetEntityType(),
                                              lhs_.GetAttributeName(),
                                              rhs_.GetLineNumber());
    }
  } else if (rhs_.IsAttributeName()) {
    // E.g. with "name" = x.varName
    if (lhs_.IsIdentifier()) {
      return queryable_pkb.QueryWithAttribute(rhs_.GetSynonym().GetEntityType(),
                                              rhs_.GetAttributeName(),
                                              lhs_.GetIdentifier());
    } else if (lhs_.IsLineNumber()) {
      // E.g. with 1 = x.stmt#
      return queryable_pkb.QueryWithAttribute(rhs_.GetSynonym().GetEntityType(),
                                              rhs_.GetAttributeName(),
                                              lhs_.GetLineNumber());
    }
  }
  assert(false);
  return {};
}

std::unordered_set<std::string> With::FetchPossibleRhs(
    std::string lhs, const QueryablePkb& queryable_pkb) const {
  return queryable_pkb.QueryWithAttributeValue(
      rhs_.GetSynonym().GetEntityType(), rhs_.GetAttributeName(), lhs);
}

std::unordered_set<std::string> With::FetchPossibleLhs(
    std::string rhs, const QueryablePkb& queryable_pkb) const {
  return queryable_pkb.QueryWithAttributeValue(
      lhs_.GetSynonym().GetEntityType(), lhs_.GetAttributeName(), rhs);
}

QueryOperation::Type With::GetType() const {
  if (rhs_.IsSynonym() && lhs_.IsSynonym()) {
    return DOUBLE_SYNONYM;
  } else if (rhs_.IsSynonym() || lhs_.IsSynonym()) {
    return SINGLE_SYNONYM;
  } else {
    return NO_SYNONYM;
  }
}

Synonym With::GetSynonym() const {
  assert(GetType() == QueryOperation::SINGLE_SYNONYM);
  return lhs_.GetSynonym();
}

std::pair<Synonym, Synonym> With::GetSynonymPair() const {
  assert(GetType() == QueryOperation::DOUBLE_SYNONYM);
  return {lhs_.GetSynonym(), rhs_.GetSynonym()};
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

bool With::IsTrue(const QueryablePkb& queryable_pkb) const { return false; }
