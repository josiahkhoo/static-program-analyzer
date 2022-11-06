#include "modifies_p_storable.h"

ModifiesPStorable::ModifiesPStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store ModifiesP Abstractions
/// \param abstractions List of abstractions
void ModifiesPStorable::Store(std::vector<ModifiesPAbstraction> abstractions) {
  for (const ModifiesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
