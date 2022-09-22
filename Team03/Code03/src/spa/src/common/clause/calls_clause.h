#ifndef SPA_CALLS_CLAUSE_H
#define SPA_CALLS_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"

class CallsClause : public Clause {
 public:
  CallsClause(EntityReference lhs, EntityReference rhs);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  EntityReference lhs_;
  EntityReference rhs_;
};

#endif  // SPA_CALLS_CLAUSE_H
