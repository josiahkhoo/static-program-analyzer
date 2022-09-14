#include "uses_p_abstraction.h"

UsesPAbstraction::UsesPAbstraction(ProcedureEntity lhs, VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const ProcedureEntity &UsesPAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const VariableEntity &UsesPAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool UsesPAbstraction::operator==(const UsesPAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool UsesPAbstraction::operator!=(const UsesPAbstraction &rhs) const {
  return !(rhs == *this);
}
