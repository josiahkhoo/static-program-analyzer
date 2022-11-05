//
// Created by kohha on 5/11/2022.
//

#include "typed_queryable_pkb.h"

TypedQueryablePkb::TypedQueryablePkb(RelationshipManager& relationship_manager_,
                                     EntityQueryable& entity_queryable_)
    : follows_queryable_(relationship_manager_, entity_queryable_) {}

FollowsQueryable& TypedQueryablePkb::GetFollowsQueryable() {
  return follows_queryable_;
}
