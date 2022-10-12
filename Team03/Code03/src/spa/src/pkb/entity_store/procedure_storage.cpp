#include "procedure_storage.h"

ProcedureStorage::ProcedureStorage() {}

void ProcedureStorage::AddProcedure(ProcedureEntity procedure) {
  procedureList.emplace(procedure.GetName());
}

std::unordered_set<std::string> ProcedureStorage::GetProcedures() const {
  return procedureList;
}
