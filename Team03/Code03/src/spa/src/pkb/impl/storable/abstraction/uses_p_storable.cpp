//
// Created by kohha on 5/11/2022.
//

#include "uses_p_storable.h"

UsesPStorable::UsesPStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store UsesP Abstractions
/// \param abstractions List of abstractions
void UsesPStorable::Store(std::vector<UsesPAbstraction> abstractions) {
  for (const UsesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
