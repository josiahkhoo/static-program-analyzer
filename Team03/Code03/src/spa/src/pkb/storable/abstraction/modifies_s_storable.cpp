//
// Created by kohha on 5/11/2022.
//

#include "modifies_s_storable.h"

ModifiesSStorable::ModifiesSStorable() = default;

/// Store ModifiesS Abstractions
/// \param abstractions List of abstractions
void ModifiesSStorable::Store(std::vector<ModifiesSAbstraction> abstractions) {
  for (const ModifiesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
