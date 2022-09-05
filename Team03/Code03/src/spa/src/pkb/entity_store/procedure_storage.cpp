#include "procedure_storage.h"

std::unordered_set<std::string> ProcedureStorage::procedureList;

ProcedureStorage::ProcedureStorage() {}

void ProcedureStorage::AddProcedure(ProcedureEntity procedure) {
  procedureList.emplace(procedure.GetName());
}

std::unordered_set<std::string> ProcedureStorage::GetProcedures() {
  return procedureList;
}

void ProcedureStorage::Clear() { procedureList.clear(); }
