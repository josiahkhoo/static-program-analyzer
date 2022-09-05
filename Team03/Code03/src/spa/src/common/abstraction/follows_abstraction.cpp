#include "follows_abstraction.h"

FollowsAbstraction::FollowsAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &FollowsAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const StatementEntity &FollowsAbstraction::GetRightHandSide() const {
  return rhs_;
}

bool FollowsAbstraction::operator==(const FollowsAbstraction &rhs) const {
  return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool FollowsAbstraction::operator!=(const FollowsAbstraction &rhs) const {
  return !(rhs == *this);
}
