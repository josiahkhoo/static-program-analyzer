#ifndef SPA_ENTITY_MANAGER_H
#define SPA_ENTITY_MANAGER_H

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

#include "procedure_storage.h"
#include "statement_storage.h"
#include "variable_storage.h"
#include "constant_storage.h"

class EntityManager {
public:
    EntityManager();
    /* ====================================
     * General Entity Adder Methods
     * ==================================== */
    // store procedure to ProcedureStorage
    void addProcedure(ProcedureEntity procedure);

    // store variable to VariableStorage
    void addVariable(VariableEntity variable);

    // store constant to ConstantStorage
    void addConstant(ConstantEntity constant);

    // store call statement to StatementStorage
    void addCallStatement(CallEntity statement);

    // store read statement to StatementStorage
    void addReadStatement(ReadEntity statement);

    // store print statement to StatementStorage
    void addPrintStatement(PrintEntity statement);

    // store assign statement to StatementStorage
    void addAssignStatement(AssignEntity statement);

    // store if statement to StatementStorage
    void addIfStatement(IfEntity statement);

    // store while statement to StatementStorage
    void addWhileStatement(WhileEntity statement);

    /* ====================================
     * General Entity Getter Methods
     * ==================================== */
    // get stored procedures in ProcedureStorage
    std::unordered_set<std::string> getProcedures();

    // get stored variables in VariableStorage
    std::unordered_set<std::string> getVariables();

    // get stored constants in ConstantStorage
    std::unordered_set<std::string> getConstants();

    // get stored statements in StatementStorage
    std::unordered_set<std::string> getStatements();

    // get stored call statements in StatementStorage
    std::unordered_set<std::string> getCallStatements();

    // get stored read statements in StatementStorage
    std::unordered_set<std::string> getReadStatements();

    // get stored print statements in StatementStorage
    std::unordered_set<std::string> getPrintStatements();

    // get stored assign statements in StatementStorage
    std::unordered_set<std::string> getAssignStatements();

    // get stored if statements in StatementStorage
    std::unordered_set<std::string> getIfStatements();

    // get stored while statements in StatementStorage
    std::unordered_set<std::string> getWhileStatements();

    /* ====================================
     * Clear All Entity Storages
     * ==================================== */
    void clear();

private:
    static ProcedureStorage procedureStore;
    static StatementStorage statementStore;
    static VariableStorage variableStore;
    static ConstantStorage constantStore;
};

#endif // SPA_ENTITY_MANAGER_H
