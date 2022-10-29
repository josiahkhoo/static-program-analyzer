#ifndef QUERY_PARSER_CPP_AFFECTS_T_CLAUSE_H
#define QUERY_PARSER_CPP_AFFECTS_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class AffectsTClause : public Clause {
 public:
  AffectsTClause(StatementReference lhs, StatementReference rhs);

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

  [[nodiscard]] std::unordered_set<std::string> FetchRhs(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchLhs(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] bool IsTrue(const QueryablePkb &queryable_pkb) const override;
  Speed GetSpeed() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
};

#endif  // QUERY_PARSER_CPP_AFFECTS_T_CLAUSE_H
