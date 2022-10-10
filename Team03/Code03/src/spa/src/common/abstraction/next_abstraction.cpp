#include "next_abstraction.h"

NextAbstraction::NextAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &NextAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const StatementEntity &NextAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool NextAbstraction::operator==(const NextAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool NextAbstraction::operator!=(const NextAbstraction &rhs) const {
  return !(rhs == *this);
}

