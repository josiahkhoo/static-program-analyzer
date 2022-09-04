#include "follows_t_clause.h"

#include <utility>

FollowsTClause::FollowsTClause(StatementReference lhs, StatementReference rhs)
    : Clause(lhs, rhs) {}

// const StatementReference& FollowsTClause::GetLeftHandSide() const {
//   return lhs_;
// }
//
// const StatementReference& FollowsTClause::GetRightHandSide() const {
//   return rhs_;
// }
//
//  const std::vector<Entity> FollowsTClause::Filter(QueryablePkb& pkb) {
//    return pkb.query(*this);
//    return {};
//  }
