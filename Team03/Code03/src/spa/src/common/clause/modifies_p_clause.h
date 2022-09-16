#ifndef SPA_MODIFIES_P_CLAUSE_H
#define SPA_MODIFIES_P_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"

class ModifiesPClause : public Clause {
 public:
  ModifiesPClause(EntityReference lhs, EntityReference rhs);

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] const Reference &GetLeftHandSide() const override;

  [[nodiscard]] const Reference &GetRightHandSide() const override;

 private:
  EntityReference lhs_;
  EntityReference rhs_;
};

#endif  // SPA_MODIFIES_P_CLAUSE_H
