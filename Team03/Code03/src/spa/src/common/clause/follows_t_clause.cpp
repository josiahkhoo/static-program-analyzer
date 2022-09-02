#include "follows_t_clause.h"

#include <utility>

FollowsTClause::FollowsTClause(StatementReference lhs, StatementReference rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

const StatementReference& FollowsTClause::GetLeftHandSide() const {
  return lhs_;
}

const StatementReference& FollowsTClause::GetRightHandSide() const {
  return rhs_;
}
