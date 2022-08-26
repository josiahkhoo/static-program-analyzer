#ifndef SPA_MODIFIES_S_CLAUSE_H
#define SPA_MODIFIES_S_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"
#include "common/reference/statement_reference.h"

class ModifiesSClause : public Clause<StatementReference, EntityReference> {
  const StatementReference &GetLeftHandSide() const override;

  const EntityReference &GetRightHandSide() const override;
};
#endif  // SPA_MODIFIES_S_CLAUSE_H
