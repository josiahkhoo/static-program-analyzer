//
// Created by Josiah Khoo on 24/8/22.
//

#include "parent_t_abstraction.h"

ParentTAbstraction::ParentTAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &ParentTAbstraction::GetLeftHandSide() const { return lhs_; }

const StatementEntity &ParentTAbstraction::GetRightHandSide() const { return rhs_; }