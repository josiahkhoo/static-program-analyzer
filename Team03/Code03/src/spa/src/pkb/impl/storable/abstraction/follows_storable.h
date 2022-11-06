#ifndef SPA_FOLLOWS_STORABLE_H
#define SPA_FOLLOWS_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class FollowsStorable : RelationshipAbstractionStorable,
                        StorablePkb<FollowsAbstraction> {
 public:
  explicit FollowsStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<FollowsAbstraction> abstractions) override;
};

#endif  // SPA_FOLLOWS_STORABLE_H
