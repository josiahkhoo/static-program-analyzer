#include "modifies_s_abstraction.h"

ModifiesSAbstraction::ModifiesSAbstraction(StatementEntity lhs,
                                           VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &ModifiesSAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const VariableEntity &ModifiesSAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool ModifiesSAbstraction::operator==(const ModifiesSAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool ModifiesSAbstraction::operator!=(const ModifiesSAbstraction &rhs) const {
  return !(rhs == *this);
}
