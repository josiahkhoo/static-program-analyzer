#include "calls_abstraction.h"

CallsAbstraction::CallsAbstraction(ProcedureEntity lhs, ProcedureEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const ProcedureEntity &CallsAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const ProcedureEntity &CallsAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool CallsAbstraction::operator==(const CallsAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool CallsAbstraction::operator!=(const CallsAbstraction &rhs) const {
  return !(rhs == *this);
}
