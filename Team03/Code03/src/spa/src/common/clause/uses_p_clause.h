#ifndef SPA_USES_P_CLAUSE_H
#define SPA_USES_P_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"

class UsesPClause : public Clause {
 public:
  UsesPClause(EntityReference lhs, EntityReference rhs);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  EntityReference lhs_;
  EntityReference rhs_;
};

#endif  // SPA_USES_P_CLAUSE_H
