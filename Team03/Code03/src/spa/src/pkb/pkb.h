#ifndef SPA_PKB_H
#define SPA_PKB_H

#include "common/queryable_pkb.h"
#include "common/storable_pkb.h"
#include "pkb/impl/queryable_pkb_impl.h"
#include "pkb/impl/storable_pkb_impl.h"

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

  // Calls
  void Store(std::vector<CallsAbstraction> abstractions) override;

  // CallsT
  void Store(std::vector<CallsTAbstraction> abstractions) override;

  // WhilePattern
  void Store(std::vector<WhilePatternAbstraction> abstractions) override;

  // IfPattern
  void Store(std::vector<IfPatternAbstraction> abstractions) override;

  // CFGs
  void Store(std::vector<CFG> cfgs) override;

  /* ====================================
   * Entity Query Methods
   * ==================================== */

  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType type) const override;

  /* ====================================
   * Relationship Query Methods
   * ==================================== */

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const override;

  // Uses query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const override;

  // Modifies query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int statement_number) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string identifier, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string identifier) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string identifier) const override;

  // Calls query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls() const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string identifier) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string identifier) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string identifier) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier) const override;

  // Next query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int statement_number, EntityType type) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryNextT(
      int statement_number, EntityType type) override;
  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type) override;

  // Affects query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllAffects() override;
  [[nodiscard]] std::unordered_set<std::string> QueryAllAffectsBy() override;
  [[nodiscard]] std::unordered_set<std::string> QueryAffects(
      int statement_number) override;
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsBy(
      int statement_number) override;
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsT(
      int statement_number) override;
  [[nodiscard]] std::unordered_set<std::string> QueryAffectsTBy(
      int statement_number) override;

  // Assign pattern query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression exp) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string lhs, Expression exp) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int statement_number) const override;

  // While pattern query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllWhilePattern()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryWhilePattern(
      std::string ident) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int statement_number) const override;

  // If pattern query methods
  [[nodiscard]] std::unordered_set<std::string> QueryAllIfPattern()
      const override;
  [[nodiscard]] std::unordered_set<std::string> QueryIfPattern(
      std::string ident) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int statement_number) const override;

  // With query methods
  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType type, int statement_number) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name,
      std::string identifier) const override;
  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, int number) const override;
  [[nodiscard]] bool CheckValidAffectsStmtNo(int stmt_no) const override;

 private:
  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
  StorablePkbImpl storable_pkb_impl_;
  QueryablePkbImpl queryable_pkb_impl_;
};

#endif  // SPA_PKB_H
