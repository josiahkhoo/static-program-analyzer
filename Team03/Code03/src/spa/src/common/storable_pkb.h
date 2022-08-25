//
// Created by Josiah Khoo on 25/8/22.
//

#ifndef SPA_STORABLE_PKB_H
#define SPA_STORABLE_PKB_H

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
#include "common/storable.h"

class StorablePkb : public Storable<AssignEntity>,
                    public Storable<CallEntity>,
                    public Storable<ConstantEntity>,
                    public Storable<IfEntity>,
                    public Storable<PrintEntity>,
                    public Storable<ProcedureEntity>,
                    public Storable<ReadEntity>,
                    public Storable<VariableEntity>,
                    public Storable<WhileEntity>,
                    public Storable<FollowsAbstraction>,
                    public Storable<FollowsTAbstraction>,
                    public Storable<ModifiesSAbstraction>,
                    public Storable<ParentAbstraction>,
                    public Storable<ParentTAbstraction>,
                    public Storable<UsesSAbstraction> {};

#endif  // SPA_STORABLE_PKB_H
