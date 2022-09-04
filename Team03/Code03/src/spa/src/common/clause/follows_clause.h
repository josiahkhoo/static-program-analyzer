#ifndef SPA_FOLLOWS_CLAUSE_H
#define SPA_FOLLOWS_CLAUSE_H

#include "clause.h"
#include "common/reference/statement_reference.h"

class FollowsClause : public Clause {
 public:
  FollowsClause(StatementReference lhs, StatementReference rhs);
};

#endif  // SPA_FOLLOWS_CLAUSE_H
