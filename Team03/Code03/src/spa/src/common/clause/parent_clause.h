#ifndef SPA_PARENT_CLAUSE_H
#define SPA_PARENT_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class ParentClause : public Clause<StatementReference, StatementReference> {
  const StatementReference &GetLeftHandSide() const override;

  const StatementReference &GetRightHandSide() const override;
};

#endif  // SPA_PARENT_CLAUSE_H
