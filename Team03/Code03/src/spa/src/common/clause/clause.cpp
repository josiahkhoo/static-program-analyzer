#include "clause.h"

std::string Clause::GetSyn() const {
  if (GetLeftHandSide().IsSynonym()) {
    return GetLeftHandSide().GetIdentifier();
  }
  if (GetRightHandSide().IsSynonym()) {
    return GetRightHandSide().GetSynonym().GetIdentifier();
  }
  return "none";
}