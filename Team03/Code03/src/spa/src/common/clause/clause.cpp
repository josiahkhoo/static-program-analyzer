#include "clause.h"

#include <utility>

Clause::Clause(Reference lhs, Reference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

const Reference &Clause::GetLeftHandSide() const { return lhs_; }

const Reference &Clause::GetRightHandSide() const { return rhs_; }

bool Clause::operator==(const Clause &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool Clause::operator!=(const Clause &rhs) const { return !(rhs == *this); }
