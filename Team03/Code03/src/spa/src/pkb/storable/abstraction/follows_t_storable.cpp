//
// Created by kohha on 5/11/2022.
//

#include "follows_t_storable.h"

FollowsTStorable::FollowsTStorable() = default;

/// Store FollowsT Abstractions
/// \param abstractions List of abstractions
void FollowsTStorable::Store(std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
