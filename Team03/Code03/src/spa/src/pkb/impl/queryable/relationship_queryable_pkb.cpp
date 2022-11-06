//
// Created by kohha on 5/11/2022.
//

#include "relationship_queryable_pkb.h"

RelationshipQueryablePkb::RelationshipQueryablePkb(
    RelationshipManager& relationship_manager_,
    EntityQueryable& entity_queryable_)
    : follows_queryable_(relationship_manager_, entity_queryable_),
      parent_queryable_(relationship_manager_, entity_queryable_),
      modifies_queryable_(relationship_manager_, entity_queryable_),
      uses_queryable_(relationship_manager_, entity_queryable_),
      calls_queryable_(relationship_manager_),
      cfg_queryable_(relationship_manager_, entity_queryable_),
      affects_queryable_(relationship_manager_, entity_queryable_) {}

/// Get FollowsQueryable
/// \return FollowsQueryable
FollowsQueryable& RelationshipQueryablePkb::GetFollowsQueryable() {
  return follows_queryable_;
}

/// Get ParentQueryable
/// \return ParentQueryable
ParentQueryable& RelationshipQueryablePkb::GetParentQueryable() {
  return parent_queryable_;
}

/// Get ModifiesQueryable
/// \return ModifiesQueryable
ModifiesQueryable& RelationshipQueryablePkb::GetModifiesQueryable() {
  return modifies_queryable_;
}

/// Get UsesQueryable
/// \return UsesQueryable
UsesQueryable& RelationshipQueryablePkb::GetUsesQueryable() {
  return uses_queryable_;
}

/// Get CallsQueryable
/// \return CallsQueryable
CallsQueryable& RelationshipQueryablePkb::GetCallsQueryable() {
  return calls_queryable_;
}

/// Get CfgQueryable
/// \return CfgQueryable
CfgQueryable& RelationshipQueryablePkb::GetCfgQueryable() {
  return cfg_queryable_;
}

/// Get AffectsQueryable
/// \return AffectsQueryable
AffectsQueryable& RelationshipQueryablePkb::GetAffectsQueryable() {
  return affects_queryable_;
}
