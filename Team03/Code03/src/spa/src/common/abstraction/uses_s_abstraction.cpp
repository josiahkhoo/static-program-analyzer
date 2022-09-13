#include "uses_s_abstraction.h"

UsesSAbstraction::UsesSAbstraction(StatementEntity lhs, VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &UsesSAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const VariableEntity &UsesSAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool UsesSAbstraction::operator==(const UsesSAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool UsesSAbstraction::operator!=(const UsesSAbstraction &rhs) const {
  return !(rhs == *this);
}
