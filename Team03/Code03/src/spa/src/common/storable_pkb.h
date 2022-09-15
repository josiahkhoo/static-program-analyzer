#ifndef SPA_STORABLE_PKB_H
#define SPA_STORABLE_PKB_H

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/while_entity.h"

class StorablePkb {
 public:
  virtual void Store(std::vector<AssignEntity> entities) = 0;

  virtual void Store(std::vector<CallEntity> entities) = 0;

  virtual void Store(std::vector<ConstantEntity> entities) = 0;

  virtual void Store(std::vector<IfEntity> entities) = 0;

  virtual void Store(std::vector<PrintEntity> entities) = 0;

  virtual void Store(std::vector<ProcedureEntity> entities) = 0;

  virtual void Store(std::vector<ReadEntity> entities) = 0;

  virtual void Store(std::vector<VariableEntity> entities) = 0;

  virtual void Store(std::vector<WhileEntity> entities) = 0;

  virtual void Store(std::vector<FollowsAbstraction> abstractions) = 0;

  virtual void Store(std::vector<FollowsTAbstraction> abstractions) = 0;

  virtual void Store(std::vector<ParentAbstraction> abstractions) = 0;

  virtual void Store(std::vector<ParentTAbstraction> abstractions) = 0;

  virtual void Store(std::vector<UsesSAbstraction> abstractions) = 0;

  virtual void Store(std::vector<UsesPAbstraction> abstractions) = 0;

  virtual void Store(std::vector<ModifiesSAbstraction> abstractions) = 0;

  virtual void Store(std::vector<ModifiesPAbstraction> abstractions) = 0;
};

#endif  // SPA_STORABLE_PKB_H
