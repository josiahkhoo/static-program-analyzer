//
// Created by Josiah Khoo on 24/8/22.
//

#include "uses_s_abstraction.h"

UsesSAbstraction::UsesSAbstraction(StatementEntity lhs, StatementEntity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &UsesSAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const StatementEntity &UsesSAbstraction::GetRightHandSide() const {
  return rhs_;
}
