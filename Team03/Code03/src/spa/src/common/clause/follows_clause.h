#ifndef SPA_FOLLOWS_CLAUSE_H
#define SPA_FOLLOWS_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsClause : public Clause<StatementReference, StatementReference> {
 public:
  FollowsClause(StatementReference lhs, StatementReference rhs);
  [[nodiscard]] const StatementReference &GetLeftHandSide() const override;
  [[nodiscard]] const StatementReference &GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_FOLLOWS_CLAUSE_H
