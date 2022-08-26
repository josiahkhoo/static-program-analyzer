//
// Created by Josiah Khoo on 25/8/22.
//

#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/while_entity.h"
#include "common/queryable.h"
#include "common/uniqueryable.h"

class QueryablePkb : public Queryable<AssignEntity>,
                     public Queryable<CallEntity>,
                     public Queryable<ConstantEntity>,
                     public Queryable<IfEntity>,
                     public Queryable<PrintEntity>,
                     public Queryable<ProcedureEntity>,
                     public Queryable<ReadEntity>,
                     public Queryable<VariableEntity>,
                     public Queryable<WhileEntity>,

                     public Uniqueryable<FollowsAbstraction, AssignEntity>,
                     public Uniqueryable<FollowsTAbstraction, AssignEntity>,
                     public Uniqueryable<ModifiesSAbstraction, AssignEntity>,
                     public Uniqueryable<ParentAbstraction, AssignEntity>,
                     public Uniqueryable<ParentTAbstraction, AssignEntity>,
                     public Uniqueryable<UsesSAbstraction, AssignEntity>,

                     public Uniqueryable<FollowsAbstraction, CallEntity>,
                     public Uniqueryable<FollowsTAbstraction, CallEntity>,
                     public Uniqueryable<ModifiesSAbstraction, CallEntity>,
                     public Uniqueryable<ParentAbstraction, CallEntity>,
                     public Uniqueryable<ParentTAbstraction, CallEntity>,
                     public Uniqueryable<UsesSAbstraction, CallEntity>,

                     public Uniqueryable<FollowsAbstraction, ConstantEntity>,
                     public Uniqueryable<FollowsTAbstraction, ConstantEntity>,
                     public Uniqueryable<ModifiesSAbstraction, ConstantEntity>,
                     public Uniqueryable<ParentAbstraction, ConstantEntity>,
                     public Uniqueryable<ParentTAbstraction, ConstantEntity>,
                     public Uniqueryable<UsesSAbstraction, ConstantEntity>,

                     public Uniqueryable<FollowsAbstraction, IfEntity>,
                     public Uniqueryable<FollowsTAbstraction, IfEntity>,
                     public Uniqueryable<ModifiesSAbstraction, IfEntity>,
                     public Uniqueryable<ParentAbstraction, IfEntity>,
                     public Uniqueryable<ParentTAbstraction, IfEntity>,
                     public Uniqueryable<UsesSAbstraction, IfEntity>,

                     public Uniqueryable<FollowsAbstraction, PrintEntity>,
                     public Uniqueryable<FollowsTAbstraction, PrintEntity>,
                     public Uniqueryable<ModifiesSAbstraction, PrintEntity>,
                     public Uniqueryable<ParentAbstraction, PrintEntity>,
                     public Uniqueryable<ParentTAbstraction, PrintEntity>,
                     public Uniqueryable<UsesSAbstraction, PrintEntity>,

                     public Uniqueryable<FollowsAbstraction, ProcedureEntity>,
                     public Uniqueryable<FollowsTAbstraction, ProcedureEntity>,
                     public Uniqueryable<ModifiesSAbstraction, ProcedureEntity>,
                     public Uniqueryable<ParentAbstraction, ProcedureEntity>,
                     public Uniqueryable<ParentTAbstraction, ProcedureEntity>,
                     public Uniqueryable<UsesSAbstraction, ProcedureEntity>,

                     public Uniqueryable<FollowsAbstraction, ReadEntity>,
                     public Uniqueryable<FollowsTAbstraction, ReadEntity>,
                     public Uniqueryable<ModifiesSAbstraction, ReadEntity>,
                     public Uniqueryable<ParentAbstraction, ReadEntity>,
                     public Uniqueryable<ParentTAbstraction, ReadEntity>,
                     public Uniqueryable<UsesSAbstraction, ReadEntity>,

                     public Uniqueryable<FollowsAbstraction, VariableEntity>,
                     public Uniqueryable<FollowsTAbstraction, VariableEntity>,
                     public Uniqueryable<ModifiesSAbstraction, VariableEntity>,
                     public Uniqueryable<ParentAbstraction, VariableEntity>,
                     public Uniqueryable<ParentTAbstraction, VariableEntity>,
                     public Uniqueryable<UsesSAbstraction, VariableEntity>,

                     public Uniqueryable<FollowsAbstraction, WhileEntity>,
                     public Uniqueryable<FollowsTAbstraction, WhileEntity>,
                     public Uniqueryable<ModifiesSAbstraction, WhileEntity>,
                     public Uniqueryable<ParentAbstraction, WhileEntity>,
                     public Uniqueryable<ParentTAbstraction, WhileEntity>,
                     public Uniqueryable<UsesSAbstraction, WhileEntity> {};

#endif  // SPA_QUERYABLE_PKB_H
