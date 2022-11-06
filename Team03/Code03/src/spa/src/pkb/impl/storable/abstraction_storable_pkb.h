#ifndef SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
#define SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H

#include "pkb/pattern_store/pattern_manager.h"
#include "pkb/relationship_store/relationship_manager.h"

class AbstractionStorablePkb {
 public:
  AbstractionStorablePkb(RelationshipManager& relationship_manager_,
                         PatternManager& pattern_manager_);

  void Store(std::vector<FollowsAbstraction> abstractions);

  void Store(std::vector<FollowsTAbstraction> abstractions);

  void Store(std::vector<ParentAbstraction> abstractions);

  void Store(std::vector<ParentTAbstraction> abstractions);

  void Store(std::vector<UsesSAbstraction> abstractions);

  void Store(std::vector<UsesPAbstraction> abstractions);

  void Store(std::vector<ModifiesSAbstraction> abstractions);

  void Store(std::vector<ModifiesPAbstraction> abstractions);

  void Store(std::vector<CallsAbstraction> abstractions);

  void Store(std::vector<CallsTAbstraction> abstractions);

  void Store(std::vector<WhilePatternAbstraction> abstractions);

  void Store(std::vector<IfPatternAbstraction> abstractions);

  void Store(std::vector<CFG> cfgs);

 private:
  RelationshipManager& relationship_manager_;
  PatternManager& pattern_manager_;
};

#endif  // SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
