#include "parent_abstraction.h"

ParentAbstraction::ParentAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &ParentAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const StatementEntity &ParentAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool ParentAbstraction::operator==(const ParentAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool ParentAbstraction::operator!=(const ParentAbstraction &rhs) const {
  return !(rhs == *this);
}
