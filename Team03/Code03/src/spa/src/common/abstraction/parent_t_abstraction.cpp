#include "parent_t_abstraction.h"

ParentTAbstraction::ParentTAbstraction(StatementEntity lhs, StatementEntity rhs)
        : lhs_(lhs), rhs_(rhs) {}

const StatementEntity &ParentTAbstraction::GetLeftHandSide() const {
    return lhs_;
}

const StatementEntity &ParentTAbstraction::GetRightHandSide() const {
    return rhs_;
}

bool ParentTAbstraction::operator==(const ParentTAbstraction &rhs) const {
    return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool ParentTAbstraction::operator!=(const ParentTAbstraction &rhs) const {
    return !(rhs == *this);
}
