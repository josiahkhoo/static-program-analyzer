//
// Created by kohha on 5/11/2022.
//

#include "modifies_p_storable.h"

ModifiesPStorable::ModifiesPStorable() = default;

/// Store ModifiesP Abstractions
/// \param abstractions List of abstractions
void ModifiesPStorable::Store(std::vector<ModifiesPAbstraction> abstractions) {
  for (const ModifiesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
