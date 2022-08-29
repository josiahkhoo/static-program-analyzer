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
