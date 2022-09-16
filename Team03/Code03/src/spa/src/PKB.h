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
#include "pkb/pattern_store/pattern_manager.h"
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

  void Store(std::vector<AssignEntity> ts)
      override;  // Store both assign entity and pattern to statement storage
                 // and pattern storage respectively

  void Store(std::vector<IfEntity> ts) override;

  void Store(std::vector<WhileEntity> ts) override;

  /* ====================================
   * Relationship Store Methods
   * ==================================== */
  // Follows
  void Store(std::vector<FollowsAbstraction> abstractions) override;

  // FollowsT
  void Store(std::vector<FollowsTAbstraction> abstractions) override;

  // Parent
  void Store(std::vector<ParentAbstraction> abstractions) override;

  // ParentT
  void Store(std::vector<ParentTAbstraction> abstractions) override;

  // UsesS
  void Store(std::vector<UsesSAbstraction> abstractions) override;

  // UsesP
  void Store(std::vector<UsesPAbstraction> abstractions) override;

  // ModifiesS
  void Store(std::vector<ModifiesSAbstraction> abstractions) override;

  // ModifiesP
  void Store(std::vector<ModifiesPAbstraction> abstractions) override;

  /* ====================================
   * Entity Query Methods
   * ==================================== */

  std::unordered_set<std::string> QueryAll(EntityType type) const override;

  /* ====================================
   * Relationship Query Methods
   * ==================================== */

  std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllFollowsRelations() const override;
  std::unordered_set<std::string> QueryFollows(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsT(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryAllParent(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const override;
  std::unordered_set<std::string> QueryAllParentsRelations() const override;
  std::unordered_set<std::string> QueryParent(int statement_number,
                                              EntityType type) const override;
  std::unordered_set<std::string> QueryParentBy(int statement_number,
                                                EntityType type) const override;
  std::unordered_set<std::string> QueryParentT(int statement_number,
                                               EntityType type) const override;
  std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const override;
  std::unordered_set<std::string> QueryAllPattern(
      Expression exp) const override;
  std::unordered_set<std::string> QueryPattern(EntityType type,
                                               Expression exp) const override;
  std::unordered_set<std::string> QueryPattern(std::string lhs,
                                               Expression exp) const override;
  std::unordered_set<std::string> GetUsesP() const override;
  std::unordered_set<std::string> GetUsesP(
      std::string uses_name) const override;
  std::unordered_set<std::string> GetUsesPBy() const override;
  std::unordered_set<std::string> GetUsesPBy(
      std::string variable_name) const override;
  std::unordered_set<std::string> GetUsesS() const override;
  std::unordered_set<std::string> GetUsesS(
      std::string uses_name) const override;
  std::unordered_set<std::string> GetUsesSBy() const override;
  std::unordered_set<std::string> GetUsesSBy(
      std::string variable_name) const override;

 private:
  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
};

#endif  // SPA_PKB_H
