#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/clause/follows_clause.h"
#include "common/clause/follows_t_clause.h"
#include "common/clause/modifies_s_clause.h"
#include "common/clause/parent_clause.h"
#include "common/clause/parent_t_clause.h"
#include "common/clause/uses_s_clause.h"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/while_entity.h"
#include "common/queryable.h"
#include "common/queryable_one_arg.h"

class QueryablePkb : public QueryableWithOneArg<EntityReference, std::string>,
                     public QueryableWithOneArg<AssignEntity, std::string>,
                     public QueryableWithOneArg<FollowsClause, std::string>,
                     public QueryableWithOneArg<FollowsTClause, std::string>,
                     public QueryableWithOneArg<Clause, std::string> {
 public:
  std::vector<std::string> query(EntityReference t) override = 0;
  std::vector<std::string> query(Clause t) override = 0;

  std::vector<std::string> query(AssignEntity t) override = 0;
  std::vector<std::string> query(FollowsClause t) override = 0;
  std::vector<std::string> query(FollowsTClause t) override = 0;
};
#endif  // SPA_QUERYABLE_PKB_H
