//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CFG_STORABLE_H
#define SPA_CFG_STORABLE_H

#include "common/storable_pkb.h"
#include "relationship_abstraction_storable.h"

class CfgStorable : RelationshipAbstractionStorable, StorablePkb<CFG> {
 public:
  explicit CfgStorable(RelationshipManager &relationship_manager_);
  void Store(std::vector<CFG> abstractions) override;
};

#endif  // SPA_CFG_STORABLE_H
