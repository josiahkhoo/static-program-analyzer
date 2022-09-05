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

bool FollowsTAbstraction::operator==(const FollowsTAbstraction &rhs) const {
    return lhs_ == rhs.lhs_ && rhs_ == rhs.rhs_;
}

bool FollowsTAbstraction::operator!=(const FollowsTAbstraction &rhs) const {
    return !(rhs == *this);
}
