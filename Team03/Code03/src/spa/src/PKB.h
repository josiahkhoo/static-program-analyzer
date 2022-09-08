#ifndef SPA_PKB_H
#define SPA_PKB_H

#include <iostream>
#include <string>
#include <vector>

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/entity/assign_entity.h"
#include "common/entity/call_entity.h"
#include "common/entity/constant_entity.h"
#include "common/entity/entity_type.h"
#include "common/entity/if_entity.h"
#include "common/entity/print_entity.h"
#include "common/entity/procedure_entity.h"
#include "common/entity/read_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "common/entity/while_entity.h"
#include "common/queryable_pkb.h"
#include "common/storable_pkb.h"
#include "pkb/entity_store/entity_manager.h"
#include "pkb/relationship_store/relationship_manager.h"

class PKB : public QueryablePkb, public StorablePkb {
 public:
  PKB();

  /* ====================================
   * Entity Store Methods
   * ==================================== */
  // Procedures
  void Store(std::vector<ProcedureEntity> ts) override;

  // Variables
  void Store(std::vector<VariableEntity> ts) override;

  // Constants
  void Store(std::vector<ConstantEntity> ts) override;

  // Statements
  void Store(std::vector<CallEntity> ts) override;

  void Store(std::vector<ReadEntity> ts) override;

  void Store(std::vector<PrintEntity> ts) override;

  void Store(std::vector<AssignEntity> ts) override;

  void Store(std::vector<IfEntity> ts) override;

  void Store(std::vector<WhileEntity> ts) override;

  std::unordered_set<std::string> QueryAll(EntityType type) const override;

  /* ====================================
   * Abstractions Store Methods
   * ==================================== */
  // Follows
  void Store(std::vector<FollowsAbstraction> abstractions) override;

  // FollowsT
  void Store(std::vector<FollowsTAbstraction> abstractions) override;

  std::unordered_set<std::string> QueryFollows(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsT(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override;

 private:
  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
};

#endif  // SPA_PKB_H
