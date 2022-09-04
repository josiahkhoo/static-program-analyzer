#include "clause.h"

#include <utility>

Clause::Clause(Reference lhs, Reference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

const Reference &Clause::GetLeftHandSide() const { return lhs_; }

const Reference &Clause::GetRightHandSide() const { return rhs_; }
