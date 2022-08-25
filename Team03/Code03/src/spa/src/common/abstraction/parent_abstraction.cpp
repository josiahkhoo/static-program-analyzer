//
// Created by Josiah Khoo on 24/8/22.
//

#include "parent_abstraction.h"
ParentAbstraction::ParentAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}
const StatementEntity &ParentAbstraction::GetLeftHandSide() const { return lhs_; }
const StatementEntity &ParentAbstraction::GetRightHandSide() const { return rhs_; }
