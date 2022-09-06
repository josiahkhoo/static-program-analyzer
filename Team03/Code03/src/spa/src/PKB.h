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
  void store(std::vector<ProcedureEntity> ts) override;

  // Variables
  void store(std::vector<VariableEntity> ts) override;

  // Constants
  void store(std::vector<ConstantEntity> ts) override;

  // Statements
  void store(std::vector<CallEntity> ts) override;

  void store(std::vector<ReadEntity> ts) override;

  void store(std::vector<PrintEntity> ts) override;

  void store(std::vector<AssignEntity> ts) override;

  void store(std::vector<IfEntity> ts) override;

  void store(std::vector<WhileEntity> ts) override;

  std::unordered_set<std::string> QueryAll(EntityType type) const override;

  /* ====================================
   * Abstractions Store Methods
   * ==================================== */
  // Follows
  void store(std::vector<FollowsAbstraction> abstractions) override;

  // FollowsT
  void store(std::vector<FollowsTAbstraction> abstractions) override;

  std::unordered_set<std::string> QueryFollow(int statement_number,
                                              EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollow(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryFollowBy(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryFollowT(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryFollowTBy(
      int statement_number, EntityType type) const override;

 private:
  static EntityManager entityManager;
  static RelationshipManager relationshipManager;
};

#endif  // SPA_PKB_H
