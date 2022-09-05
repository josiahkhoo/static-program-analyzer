#ifndef SPA_PARENT_CLAUSE_H
#define SPA_PARENT_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class ParentClause : public Clause {
  const StatementReference &GetLeftHandSide() const;

  const StatementReference &GetRightHandSide() const;
};

#endif  // SPA_PARENT_CLAUSE_H
