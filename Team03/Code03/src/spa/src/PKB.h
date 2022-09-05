#ifndef SPA_PKB_H
#define SPA_PKB_H

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include "common/entity/constant_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/assign_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/while_entity.h"
#include "common/entity/entity_type.h"
#include "common/queryable_pkb.h"
#include "common/storable_pkb.h"
#include "pkb/entity_store/entity_manager.h"

class PKB : public QueryablePkb, public StorablePkb {
 public:
    PKB();

    /* ====================================
     * Entity Store Methods
     * ==================================== */
    // Procedures
    void store(std::vector<ProcedureEntity> ts);
    // Variables
    void store(std::vector<VariableEntity> ts);
    //Constants
    void store(std::vector<ConstantEntity> ts);
    // Statements
    void store(std::vector<CallEntity> ts);
    void store(std::vector<ReadEntity> ts);
    void store(std::vector<PrintEntity> ts);
    void store(std::vector<AssignEntity> ts);
    void store(std::vector<IfEntity> ts);
    void store(std::vector<WhileEntity> ts);

    std::unordered_set<std::string> QueryALl(EntityType type);

private:
    static EntityManager entityManager;
};

#endif // SPA_PKB_H
