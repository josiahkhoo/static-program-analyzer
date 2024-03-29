#include "clause.h"

#include <cassert>

Synonym Clause::GetSynonym() const {
  assert(GetType() == SINGLE_SYNONYM);
  if (GetLeftHandSide().IsSynonym()) {
    return GetLeftHandSide().GetSynonym();
  }
  if (GetRightHandSide().IsSynonym()) {
    return GetRightHandSide().GetSynonym();
  }
  assert(false);
}

QueryOperation::Type Clause::GetType() const {
  if (GetLeftHandSide().IsSynonym() && GetRightHandSide().IsSynonym()) {
    return DOUBLE_SYNONYM;
  } else if (!GetLeftHandSide().IsSynonym() &&
             !GetRightHandSide().IsSynonym()) {
    return NO_SYNONYM;
  } else {
    return SINGLE_SYNONYM;
  }
}

std::pair<Synonym, Synonym> Clause::GetSynonymPair() const {
  assert(GetType() == DOUBLE_SYNONYM);
  return {GetLeftHandSide().GetSynonym(), GetRightHandSide().GetSynonym()};
}

QueryOperation::IterateSide Clause::GetIterateSide(
    std::vector<std::vector<std::string>> lhs,
    std::vector<std::vector<std::string>> rhs) const {
  if (lhs.size() > rhs.size()) {
    // Iterate over smaller side (i.e. RHS)
    return RHS;
  }
  return LHS;
}

std::unordered_set<std::string> Clause::Fetch(QueryablePkb& queryable_pkb) {
  assert(GetType() == SINGLE_SYNONYM);
  if (GetLeftHandSide().IsSynonym()) {
    return FetchLhs(queryable_pkb);
  } else {
    return FetchRhs(queryable_pkb);
  }
}