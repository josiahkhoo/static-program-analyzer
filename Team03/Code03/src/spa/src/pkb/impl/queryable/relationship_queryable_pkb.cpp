#include "relationship_queryable_pkb.h"

RelationshipQueryablePkb::RelationshipQueryablePkb(
    const RelationshipManager& relationship_manager_,
    const EntityQueryable& entity_queryable_)
    : follows_queryable_(relationship_manager_, entity_queryable_),
      parent_queryable_(relationship_manager_, entity_queryable_),
      modifies_queryable_(relationship_manager_, entity_queryable_),
      uses_queryable_(relationship_manager_, entity_queryable_),
      calls_queryable_(relationship_manager_),
      cfg_queryable_(relationship_manager_, entity_queryable_),
      affects_queryable_(relationship_manager_, entity_queryable_) {}

/// Get FollowsQueryable
/// \return FollowsQueryable
const FollowsQueryable& RelationshipQueryablePkb::GetFollowsQueryable() const {
  return follows_queryable_;
}

/// Get ParentQueryable
/// \return ParentQueryable
const ParentQueryable& RelationshipQueryablePkb::GetParentQueryable() const {
  return parent_queryable_;
}

/// Get ModifiesQueryable
/// \return ModifiesQueryable
const ModifiesQueryable& RelationshipQueryablePkb::GetModifiesQueryable() const {
  return modifies_queryable_;
}

/// Get UsesQueryable
/// \return UsesQueryable
const UsesQueryable& RelationshipQueryablePkb::GetUsesQueryable() const {
  return uses_queryable_;
}

/// Get CallsQueryable
/// \return CallsQueryable
const CallsQueryable& RelationshipQueryablePkb::GetCallsQueryable() const {
  return calls_queryable_;
}

/// Get CfgQueryable
/// \return CfgQueryable
const CfgQueryable& RelationshipQueryablePkb::GetCfgQueryable() const {
  return cfg_queryable_;
}

/// Get AffectsQueryable
/// \return AffectsQueryable
const AffectsQueryable& RelationshipQueryablePkb::GetAffectsQueryable() const {
  return affects_queryable_;
}
