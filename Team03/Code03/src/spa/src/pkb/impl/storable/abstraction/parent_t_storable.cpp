//
// Created by kohha on 5/11/2022.
//

#include "parent_t_storable.h"

ParentTStorable::ParentTStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store ParentT Abstractions
/// \param abstractions List of abstractions
void ParentTStorable::Store(std::vector<ParentTAbstraction> abstractions) {
  for (const ParentTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
