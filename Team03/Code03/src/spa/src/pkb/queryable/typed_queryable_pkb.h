//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_TYPED_QUERYABLE_PKB_H
#define SPA_TYPED_QUERYABLE_PKB_H

#include "entity_queryable.h"
#include "pkb/queryable/typed/follows_queryable.h"
#include "pkb/relationship_store/relationship_manager.h"

class TypedQueryablePkb {
 public:
  TypedQueryablePkb(RelationshipManager &relationship_manager_,
                    EntityQueryable &entity_queryable_);

  [[nodiscard]] FollowsQueryable GetFollowsQueryable() const;

 private:
  FollowsQueryable follows_queryable_;
};

#endif  // SPA_TYPED_QUERYABLE_PKB_H
