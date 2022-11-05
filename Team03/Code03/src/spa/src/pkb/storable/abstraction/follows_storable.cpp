//
// Created by kohha on 5/11/2022.
//

#include "follows_storable.h"

FollowsStorable::FollowsStorable() = default;

/// Store Follows Abstractions
/// \param abstractions List of abstractions
void FollowsStorable::Store(std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
