#ifndef SPA_FOLLOWS_T_CLAUSE_H
#define SPA_FOLLOWS_T_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsTClause : public Clause {
 public:
  FollowsTClause(StatementReference lhs, StatementReference rhs);
};

#endif  // SPA_FOLLOWS_T_CLAUSE_H
