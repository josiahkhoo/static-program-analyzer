#ifndef SPA_USES_S_CLAUSE_H
#define SPA_USES_S_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"
#include "common/reference/statement_reference.h"

class UsesSClause : public Clause {
 public:
  UsesSClause(StatementReference lhs, EntityReference rhs);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  StatementReference lhs_;
  EntityReference rhs_;
};

#endif  // SPA_USES_S_CLAUSE_H
