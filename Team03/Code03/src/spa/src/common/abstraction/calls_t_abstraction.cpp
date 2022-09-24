#include "calls_t_abstraction.h"

CallsTAbstraction::CallsTAbstraction(ProcedureEntity lhs, ProcedureEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const ProcedureEntity &CallsTAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const ProcedureEntity &CallsTAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool CallsTAbstraction::operator==(const CallsTAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool CallsTAbstraction::operator!=(const CallsTAbstraction &rhs) const {
  return !(rhs == *this);
}
