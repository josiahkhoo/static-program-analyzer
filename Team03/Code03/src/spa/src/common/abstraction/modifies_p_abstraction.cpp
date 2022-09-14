#include "modifies_p_abstraction.h"

ModifiesPAbstraction::ModifiesPAbstraction(ProcedureEntity lhs,
                                           VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const ProcedureEntity &ModifiesPAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const VariableEntity &ModifiesPAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool ModifiesPAbstraction::operator==(const ModifiesPAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool ModifiesPAbstraction::operator!=(const ModifiesPAbstraction &rhs) const {
  return !(rhs == *this);
}