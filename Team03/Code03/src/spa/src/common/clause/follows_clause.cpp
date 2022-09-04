#include "follows_clause.h"

FollowsClause::FollowsClause(StatementReference lhs, StatementReference rhs)
    : Clause(lhs, rhs) {}

// const StatementReference &FollowsClause::GetLeftHandSide() const {
//   return lhs_;
// }
//
// const StatementReference &FollowsClause::GetRightHandSide() const {
//   return rhs_;
// }
//
// const std::vector<Entity> FollowsClause::Filter(QueryablePkb &pkb) {
//   return pkb.query(*this);
//   return {};
// }
