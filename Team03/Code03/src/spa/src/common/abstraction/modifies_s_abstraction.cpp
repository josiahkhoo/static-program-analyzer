//
// Created by Josiah Khoo on 24/8/22.
//

#include "modifies_s_abstraction.h"

ModifiesSAbstraction::ModifiesSAbstraction(StatementEntity lhs, Entity rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &ModifiesSAbstraction::GetLeftHandSide() const {
  return lhs_;
}

const Entity &ModifiesSAbstraction::GetRightHandSide() const { return rhs_; }
