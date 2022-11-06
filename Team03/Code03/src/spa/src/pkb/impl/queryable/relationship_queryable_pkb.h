//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_RELATIONSHIP_QUERYABLE_PKB_H
#define SPA_RELATIONSHIP_QUERYABLE_PKB_H

#include "pkb/impl/queryable/relationship/typed/affects_queryable.h"
#include "pkb/impl/queryable/relationship/typed/cfg_queryable.h"
#include "pkb/impl/queryable/relationship/typed/follows_queryable.h"
#include "pkb/impl/queryable/relationship/typed/modifies_queryable.h"
#include "pkb/impl/queryable/relationship/typed/parent_queryable.h"
#include "pkb/impl/queryable/relationship/typed/uses_queryable.h"
#include "pkb/impl/queryable/relationship/untyped/calls_queryable.h"

class RelationshipQueryablePkb {
 public:
  RelationshipQueryablePkb(RelationshipManager& relationship_manager_,
                           EntityQueryable& entity_queryable_);

  [[nodiscard]] FollowsQueryable& GetFollowsQueryable();

  [[nodiscard]] ParentQueryable& GetParentQueryable();

  [[nodiscard]] ModifiesQueryable& GetModifiesQueryable();

  [[nodiscard]] UsesQueryable& GetUsesQueryable();

  [[nodiscard]] CallsQueryable& GetCallsQueryable();

  [[nodiscard]] CfgQueryable& GetCfgQueryable();

  [[nodiscard]] AffectsQueryable& GetAffectsQueryable();

 private:
  FollowsQueryable follows_queryable_;
  ParentQueryable parent_queryable_;
  ModifiesQueryable modifies_queryable_;
  UsesQueryable uses_queryable_;
  CallsQueryable calls_queryable_;
  CfgQueryable cfg_queryable_;
  AffectsQueryable affects_queryable_;
};

#endif  // SPA_RELATIONSHIP_QUERYABLE_PKB_H
