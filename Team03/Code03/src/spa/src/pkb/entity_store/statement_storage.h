#ifndef SPA_STATEMENT_STORAGE_H
#define SPA_STATEMENT_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>

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

    std::unordered_set<std::string> getStatements();

    std::unordered_set<std::string> getCallStatements();

    std::unordered_set<std::string> getReadStatements();

    std::unordered_set<std::string> getPrintStatements();

    std::unordered_set<std::string> getAssignStatements();

    std::unordered_set<std::string> getIfStatements();

    std::unordered_set<std::string> getWhileStatements();

    // Empty storage
    void clear();

private:
    static std::unordered_set<std::string> statementList;
    static std::unordered_set<std::string> callStatementList;
    static std::unordered_set<std::string> readStatementList;
    static std::unordered_set<std::string> printStatementList;
    static std::unordered_set<std::string> assignStatementList;
    static std::unordered_set<std::string> ifStatementList;
    static std::unordered_set<std::string> whileStatementList;
};

#endif // SPA_STATEMENT_STORAGE_H
