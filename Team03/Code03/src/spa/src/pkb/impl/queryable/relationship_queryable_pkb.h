#ifndef SPA_RELATIONSHIP_QUERYABLE_PKB_H
#define SPA_RELATIONSHIP_QUERYABLE_PKB_H

#include "pkb/impl/queryable/relationship/affects_queryable.h"
#include "pkb/impl/queryable/relationship/calls_queryable.h"
#include "pkb/impl/queryable/relationship/cfg_queryable.h"
#include "pkb/impl/queryable/relationship/follows_queryable.h"
#include "pkb/impl/queryable/relationship/modifies_queryable.h"
#include "pkb/impl/queryable/relationship/parent_queryable.h"
#include "pkb/impl/queryable/relationship/uses_queryable.h"

class RelationshipQueryablePkb {
 public:
  RelationshipQueryablePkb(const RelationshipManager& relationship_manager_,
                           const EntityQueryable& entity_queryable_);

  [[nodiscard]] const FollowsQueryable& GetFollowsQueryable() const;

  [[nodiscard]] const ParentQueryable& GetParentQueryable() const;

  [[nodiscard]] const ModifiesQueryable& GetModifiesQueryable() const;

  [[nodiscard]] const UsesQueryable& GetUsesQueryable() const;

  [[nodiscard]] const CallsQueryable& GetCallsQueryable() const;

  [[nodiscard]] const CfgQueryable& GetCfgQueryable() const;

  [[nodiscard]] const AffectsQueryable& GetAffectsQueryable() const;

 private:
  const FollowsQueryable follows_queryable_;
  const ParentQueryable parent_queryable_;
  const ModifiesQueryable modifies_queryable_;
  const UsesQueryable uses_queryable_;
  const CallsQueryable calls_queryable_;
  const CfgQueryable cfg_queryable_;
  const AffectsQueryable affects_queryable_;
};

#endif  // SPA_RELATIONSHIP_QUERYABLE_PKB_H
