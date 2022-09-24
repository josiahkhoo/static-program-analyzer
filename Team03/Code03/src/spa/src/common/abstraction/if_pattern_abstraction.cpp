#include "if_pattern_abstraction.h"

IfPatternAbstraction::IfPatternAbstraction(IfEntity lhs, VariableEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const IfEntity& IfPatternAbstraction::GetLeftHandSide() const { return lhs_; }

const VariableEntity& IfPatternAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool IfPatternAbstraction::operator==(const IfPatternAbstraction& rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool IfPatternAbstraction::operator!=(const IfPatternAbstraction& rhs) const {
  return !(rhs == *this);
}
