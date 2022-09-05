#ifndef SPA_FOLLOWS_T_CLAUSE_H
#define SPA_FOLLOWS_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsTClause : public Clause {
 public:
  FollowsTClause(StatementReference lhs, StatementReference rhs);
  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb& queryable_pkb) const override;
  [[nodiscard]] const Reference& GetLeftHandSide() const override;
  [[nodiscard]] const Reference& GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_FOLLOWS_T_CLAUSE_H
