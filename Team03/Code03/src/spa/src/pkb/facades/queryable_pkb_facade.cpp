#include "queryable_pkb_facade.h"

QueryablePkbFacade::QueryablePkbFacade(
    const EntityManager& entity_manager_,
    const RelationshipManager& relationship_manager_,
    const PatternManager& pattern_manager_)
    : entity_queryable_(entity_manager_),
      relationship_queryable_pkb_(relationship_manager_, entity_queryable_),
      pattern_queryable_pkb_(pattern_manager_) {}

/// Get EntityQueryable
/// \return EntityQueryable
const EntityQueryable& QueryablePkbFacade::GetEntityQueryable() const {
  return entity_queryable_;
}

/// Get RelationshipQueryablePkb
/// \return RelationshipQueryablePkb
const RelationshipQueryablePkb&
QueryablePkbFacade::GetRelationshipQueryablePkb() const {
  return relationship_queryable_pkb_;
}

/// Get PatternQueryablePkb
/// \return PatternQueryablePkb
const PatternQueryablePkb& QueryablePkbFacade::GetPatternQueryablePkb() const {
  return pattern_queryable_pkb_;
}
