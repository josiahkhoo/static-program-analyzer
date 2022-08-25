//
// Created by Josiah Khoo on 24/8/22.
//

#include "follows_abstraction.h"

FollowsAbstraction::FollowsAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &FollowsAbstraction::GetLeftHandSide() const { return lhs_; }

const StatementEntity &FollowsAbstraction::GetRightHandSide() const { return rhs_; }
