#include "follows_t_storable.h"

FollowsTStorable::FollowsTStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store FollowsT Abstractions
/// \param abstractions List of abstractions
void FollowsTStorable::Store(std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
