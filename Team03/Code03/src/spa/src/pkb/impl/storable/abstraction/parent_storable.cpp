//
// Created by kohha on 5/11/2022.
//

#include "parent_storable.h"

ParentStorable::ParentStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store Parent Abstractions
/// \param abstractions List of abstractions
void ParentStorable::Store(std::vector<ParentAbstraction> abstractions) {
  for (const ParentAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
