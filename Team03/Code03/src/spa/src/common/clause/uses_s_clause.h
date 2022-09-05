#ifndef SPA_USES_S_CLAUSE_H
#define SPA_USES_S_CLAUSE_H

#include "clause.h"
#include "common/reference/entity_reference.h"
#include "common/reference/statement_reference.h"

class UsesSClause : public Clause {
  const StatementReference &GetLeftHandSide() const;

  const EntityReference &GetRightHandSide() const;
};

#endif  // SPA_USES_S_CLAUSE_H
