#ifndef SPA_FOLLOWS_CLAUSE_H
#define SPA_FOLLOWS_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsClause : public Clause {
 public:
  FollowsClause(StatementReference lhs, StatementReference rhs);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // SPA_FOLLOWS_CLAUSE_H
