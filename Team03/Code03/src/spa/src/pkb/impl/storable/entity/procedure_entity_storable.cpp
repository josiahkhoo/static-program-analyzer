//
// Created by kohha on 5/11/2022.
//

#include "procedure_entity_storable.h"

ProcedureEntityStorable::ProcedureEntityStorable(EntityManager& entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store Procedure Entities
/// \param ts List of entities
void ProcedureEntityStorable::Store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entity_manager_.AddProcedure(entity);
  }
}