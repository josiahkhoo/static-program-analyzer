#include "clause.h"

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
