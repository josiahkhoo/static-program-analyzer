#include "queryable_pkb_impl.h"

QueryablePkbImpl::QueryablePkbImpl(EntityManager& entity_manager_,
                                   RelationshipManager& relationship_manager_,
                                   PatternManager& pattern_manager_)
    : entity_queryable_(entity_manager_),
      relationship_queryable_pkb_(relationship_manager_, entity_queryable_),
      pattern_queryable_pkb_(pattern_manager_) {}

/// Get EntityQueryable
/// \return EntityQueryable
EntityQueryable& QueryablePkbImpl::GetEntityQueryable() {
  return entity_queryable_;
}

/// Get RelationshipQueryablePkb
/// \return RelationshipQueryablePkb
RelationshipQueryablePkb& QueryablePkbImpl::GetRelationshipQueryablePkb() {
  return relationship_queryable_pkb_;
}

/// Get PatternQueryablePkb
/// \return PatternQueryablePkb
PatternQueryablePkb& QueryablePkbImpl::GetPatternQueryablePkb() {
  return pattern_queryable_pkb_;
}
