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

class StorablePkb {
public:
    virtual void store(std::vector<AssignEntity> entities) = 0;

    virtual void store(std::vector<CallEntity> entities) = 0;

    virtual void store(std::vector<ConstantEntity> entities) = 0;

    virtual void store(std::vector<IfEntity> entities) = 0;

    virtual void store(std::vector<PrintEntity> entities) = 0;

    virtual void store(std::vector<ProcedureEntity> entities) = 0;

    virtual void store(std::vector<ReadEntity> entities) = 0;

    virtual void store(std::vector<VariableEntity> entities) = 0;

    virtual void store(std::vector<WhileEntity> entities) = 0;

    virtual void store(std::vector<FollowsAbstraction> abstractions) = 0;

    virtual void store(std::vector<FollowsTAbstraction> abstractions) = 0;

    virtual void store(std::vector<ModifiesSAbstraction> abstractions) = 0;

    virtual void store(std::vector<ParentTAbstraction> abstractions) = 0;

    virtual void store(std::vector<UsesSAbstraction> abstractions) = 0;
};

#endif  // SPA_STORABLE_PKB_H
