//
// Created by Josiah Khoo on 24/8/22.
//

#include "follows_t_abstraction.h"

FollowsTAbstraction::FollowsTAbstraction(StatementEntity lhs,
                                         StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &FollowsTAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const StatementEntity &FollowsTAbstraction::GetRightHandSide() const {
  return rhs_;
}