#ifndef SPA_PARENT_T_CLAUSE_H
#define SPA_PARENT_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class ParentTClause : public Clause {
    const StatementReference &GetLeftHandSide() const;

    const StatementReference &GetRightHandSide() const;
};

#endif  // SPA_PARENT_T_CLAUSE_H
