#include "follows_clause.h"

FollowsClause::FollowsClause(StatementReference lhs, StatementReference rhs)
    : lhs_(lhs), rhs_(rhs) {}

const StatementReference &FollowsClause::GetLeftHandSide() const {
  return lhs_;
}

const StatementReference &FollowsClause::GetRightHandSide() const {
  return rhs_;
}
