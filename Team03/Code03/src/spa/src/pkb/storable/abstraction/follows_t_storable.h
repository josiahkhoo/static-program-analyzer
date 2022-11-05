//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_FOLLOWS_T_STORABLE_H
#define SPA_FOLLOWS_T_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class FollowsTStorable : RelationshipAbstractionStorable, StorablePkb<FollowsTAbstraction> {
 public:
  FollowsTStorable();
  void Store(std::vector<FollowsTAbstraction> abstractions) override;
};

#endif  // SPA_FOLLOWS_T_STORABLE_H
