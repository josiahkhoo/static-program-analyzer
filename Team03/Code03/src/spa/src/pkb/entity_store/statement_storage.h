#ifndef SPA_STATEMENT_STORAGE_H
#define SPA_STATEMENT_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/call_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/assign_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/while_entity.h"

class StatementStorage {
public:
    StatementStorage();

    void addCallStatement(CallEntity callEntity);
    void addReadStatement(ReadEntity readEntity);
    void addPrintStatement(PrintEntity printEntity);
    void addAssignStatement(AssignEntity assignEntity);
    void addIfStatement(IfEntity ifEntity);
    void addWhileStatement(WhileEntity whileEntity);

    std::unordered_set<int> getCallStatements();
    std::unordered_set<int> getReadStatements();
    std::unordered_set<int> getPrintStatements();
    std::unordered_set<int> getAssignStatements();
    std::unordered_set<int> getIfStatements();
    std::unordered_set<int> getWhileStatements();

    // Empty storage
    void clear();

private:
    static std::unordered_set<int> callStatementList;
    static std::unordered_set<int> readStatementList;
    static std::unordered_set<int> printStatementList;
    static std::unordered_set<int> assignStatementList;
    static std::unordered_set<int> ifStatementList;
    static std::unordered_set<int> whileStatementList;
};
#endif // SPA_STATEMENT_STORAGE_H
