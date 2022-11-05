#ifndef SPA_FOLLOWS_T_CLAUSE_H
#define SPA_FOLLOWS_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsTClause : public Clause {
 public:
  FollowsTClause(StatementReference lhs, StatementReference rhs);

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, QueryablePkb &queryable_pkb) override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, QueryablePkb &queryable_pkb) override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

  [[nodiscard]] std::unordered_set<std::string> FetchRhs(
      QueryablePkb &queryable_pkb) override;

  [[nodiscard]] std::unordered_set<std::string> FetchLhs(
      QueryablePkb &queryable_pkb) override;

  [[nodiscard]] bool IsTrue(QueryablePkb &queryable_pkb) override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_FOLLOWS_T_CLAUSE_H
