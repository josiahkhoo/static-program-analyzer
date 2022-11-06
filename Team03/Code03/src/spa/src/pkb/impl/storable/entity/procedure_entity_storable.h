#ifndef SPA_PROCEDURE_ENTITY_STORABLE_H
#define SPA_PROCEDURE_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class ProcedureEntityStorable : EntityStorable, StorablePkb<ProcedureEntity> {
 public:
  explicit ProcedureEntityStorable(EntityManager &entity_manager_);
  void Store(std::vector<ProcedureEntity> ts) override;
};

#endif  // SPA_PROCEDURE_ENTITY_STORABLE_H
