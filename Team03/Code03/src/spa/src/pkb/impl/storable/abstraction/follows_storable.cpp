#include "follows_storable.h"

FollowsStorable::FollowsStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store Follows Abstractions
/// \param abstractions List of abstractions
void FollowsStorable::Store(std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
