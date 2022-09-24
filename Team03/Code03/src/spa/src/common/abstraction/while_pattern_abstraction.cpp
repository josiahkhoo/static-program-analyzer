#include "while_pattern_abstraction.h"

WhilePatternAbstraction::WhilePatternAbstraction(WhileEntity lhs,
                                                 VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const WhileEntity& WhilePatternAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const VariableEntity& WhilePatternAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool WhilePatternAbstraction::operator==(
    const WhilePatternAbstraction& rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool WhilePatternAbstraction::operator!=(
    const WhilePatternAbstraction& rhs) const {
  return !(rhs == *this);
}
