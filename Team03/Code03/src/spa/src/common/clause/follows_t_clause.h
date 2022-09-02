#ifndef SPA_FOLLOWS_T_CLAUSE_H
#define SPA_FOLLOWS_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsTClause : public Clause<StatementReference, StatementReference> {
 public:
  FollowsTClause(StatementReference lhs, StatementReference rhs);
  [[nodiscard]] const StatementReference &GetLeftHandSide() const override;
  [[nodiscard]] const StatementReference &GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_FOLLOWS_T_CLAUSE_H
