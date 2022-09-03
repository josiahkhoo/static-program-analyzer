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

class QueryablePkb
    : public Queryable<AssignEntity>,
      public Queryable<CallEntity>,
      public Queryable<ConstantEntity>,
      public Queryable<IfEntity>,
      public Queryable<PrintEntity>,
      public Queryable<ProcedureEntity>,
      public Queryable<ReadEntity>,
      public Queryable<VariableEntity>,
      public Queryable<WhileEntity>,

      public QueryableWithOneArg<FollowsClause, AssignEntity>,
      public QueryableWithOneArg<FollowsTClause, AssignEntity>,
      public QueryableWithOneArg<ModifiesSClause, AssignEntity>,
      public QueryableWithOneArg<ParentClause, AssignEntity>,
      public QueryableWithOneArg<ParentTClause, AssignEntity>,
      public QueryableWithOneArg<UsesSClause, AssignEntity>,

      public QueryableWithOneArg<FollowsClause, CallEntity>,
      public QueryableWithOneArg<FollowsTClause, CallEntity>,
      public QueryableWithOneArg<ModifiesSClause, CallEntity>,
      public QueryableWithOneArg<ParentClause, CallEntity>,
      public QueryableWithOneArg<ParentTClause, CallEntity>,
      public QueryableWithOneArg<UsesSClause, CallEntity>,

      public QueryableWithOneArg<FollowsClause, ConstantEntity>,
      public QueryableWithOneArg<FollowsTClause, ConstantEntity>,
      public QueryableWithOneArg<ModifiesSClause, ConstantEntity>,
      public QueryableWithOneArg<ParentClause, ConstantEntity>,
      public QueryableWithOneArg<ParentTClause, ConstantEntity>,
      public QueryableWithOneArg<UsesSClause, ConstantEntity>,

      public QueryableWithOneArg<FollowsClause, IfEntity>,
      public QueryableWithOneArg<FollowsTClause, IfEntity>,
      public QueryableWithOneArg<ModifiesSClause, IfEntity>,
      public QueryableWithOneArg<ParentClause, IfEntity>,
      public QueryableWithOneArg<ParentTClause, IfEntity>,
      public QueryableWithOneArg<UsesSClause, IfEntity>,

      public QueryableWithOneArg<FollowsClause, PrintEntity>,
      public QueryableWithOneArg<FollowsTClause, PrintEntity>,
      public QueryableWithOneArg<ModifiesSClause, PrintEntity>,
      public QueryableWithOneArg<ParentClause, PrintEntity>,
      public QueryableWithOneArg<ParentTClause, PrintEntity>,
      public QueryableWithOneArg<UsesSClause, PrintEntity>,

      public QueryableWithOneArg<FollowsClause, ProcedureEntity>,
      public QueryableWithOneArg<FollowsTClause, ProcedureEntity>,
      public QueryableWithOneArg<ModifiesSClause, ProcedureEntity>,
      public QueryableWithOneArg<ParentClause, ProcedureEntity>,
      public QueryableWithOneArg<ParentTClause, ProcedureEntity>,
      public QueryableWithOneArg<UsesSClause, ProcedureEntity>,

      public QueryableWithOneArg<FollowsClause, ReadEntity>,
      public QueryableWithOneArg<FollowsTClause, ReadEntity>,
      public QueryableWithOneArg<ModifiesSClause, ReadEntity>,
      public QueryableWithOneArg<ParentClause, ReadEntity>,
      public QueryableWithOneArg<ParentTClause, ReadEntity>,
      public QueryableWithOneArg<UsesSClause, ReadEntity>,

      public QueryableWithOneArg<FollowsClause, VariableEntity>,
      public QueryableWithOneArg<FollowsTClause, VariableEntity>,
      public QueryableWithOneArg<ModifiesSClause, VariableEntity>,
      public QueryableWithOneArg<ParentClause, VariableEntity>,
      public QueryableWithOneArg<ParentTClause, VariableEntity>,
      public QueryableWithOneArg<UsesSClause, VariableEntity>,

      public QueryableWithOneArg<FollowsClause, WhileEntity>,
      public QueryableWithOneArg<FollowsTClause, WhileEntity>,
      public QueryableWithOneArg<ModifiesSClause, WhileEntity>,
      public QueryableWithOneArg<ParentClause, WhileEntity>,
      public QueryableWithOneArg<ParentTClause, WhileEntity>,
      public QueryableWithOneArg<UsesSClause, WhileEntity> {
 public:
  [[nodiscard]] std::vector<Entity> query(EntityReference e) const;
  [[nodiscard]] std::vector<Entity> query(SuchThat c) const;
};

// Temporary implementation

std::vector<Entity> QueryablePkb::query(EntityReference e) const { return {}; }

std::vector<Entity> QueryablePkb::query(SuchThat c) const { return {}; }

#endif  // SPA_QUERYABLE_PKB_H
