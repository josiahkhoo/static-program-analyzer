#include "procedure_storage.h"

std::unordered_set<std::string> ProcedureStorage::procedureList;

ProcedureStorage::ProcedureStorage() {}

void ProcedureStorage::addProcedure(ProcedureEntity procedure) {
    procedureList.emplace(procedure.GetName());
}

std::unordered_set<std::string> ProcedureStorage::getProcedures() {
    return procedureList;
}

void ProcedureStorage::clear() {
    procedureList.clear();
}
