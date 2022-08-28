#ifndef SPA_PROCEDURE_STORAGE_H
#define SPA_PROCEDURE_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/procedure_entity.h"

class ProcedureStorage {
public:
    ProcedureStorage();

    void addProcedure(ProcedureEntity procedure);

    std::unordered_set<std::string> getProcedures();

    // Empty storage
    void clear();

private:
    static std::unordered_set<std::string> procedureList;
};

#endif // SPA_PROCEDURE_STORAGE_H
