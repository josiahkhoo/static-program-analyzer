#ifndef SPA_ENTITY_STORABLE_PKB_H
#define SPA_ENTITY_STORABLE_PKB_H

#include "pkb/entity_store/entity_manager.h"
#include "pkb/pattern_store/pattern_manager.h"

class EntityStorablePkb {
 public:
  EntityStorablePkb(EntityManager& entity_manager_,
                    PatternManager& pattern_manager_);

  void Store(std::vector<ProcedureEntity> ts);

  void Store(std::vector<VariableEntity> ts);

  void Store(std::vector<ConstantEntity> ts);

  void Store(std::vector<CallEntity> ts);

  void Store(std::vector<ReadEntity> ts);

  void Store(std::vector<PrintEntity> ts);

  void Store(std::vector<AssignEntity> ts);

  void Store(std::vector<IfEntity> ts);

  void Store(std::vector<WhileEntity> ts);

 private:
  EntityManager& entity_manager_;
  PatternManager& pattern_manager_;
};

#endif  // SPA_ENTITY_STORABLE_PKB_H
