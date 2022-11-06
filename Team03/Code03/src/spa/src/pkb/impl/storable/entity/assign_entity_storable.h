#ifndef SPA_ASSIGN_ENTITY_STORABLE_H
#define SPA_ASSIGN_ENTITY_STORABLE_H

#include "common/storable_pkb.h"
#include "entity_storable.h"

class AssignEntityStorable : EntityStorable, StorablePkb<AssignEntity> {
 public:
  explicit AssignEntityStorable(EntityManager &entity_manager_,
                                PatternManager &pattern_manager_);
  void Store(std::vector<AssignEntity> ts) override;

 private:
  PatternManager &pattern_manager_;
};

#endif  // SPA_ASSIGN_ENTITY_STORABLE_H
