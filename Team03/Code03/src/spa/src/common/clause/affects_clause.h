#ifndef QUERY_PARSER_CPP_AFFECTS_CLAUSE_H
#define QUERY_PARSER_CPP_AFFECTS_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class AffectsClause : public Clause {
 public:
  AffectsClause(StatementReference lhs, StatementReference rhs);

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

  [[nodiscard]] bool IsValid(const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] Speed GetSpeed() const override;

 private:
  StatementReference lhs_;
  StatementReference rhs_;
  [[nodiscard]] bool CheckIfNotAssignStatement(const Reference &ref) const;
};

#endif  // QUERY_PARSER_CPP_AFFECTS_CLAUSE_H
