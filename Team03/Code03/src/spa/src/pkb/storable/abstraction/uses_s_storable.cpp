//
// Created by kohha on 5/11/2022.
//

#include "uses_s_storable.h"

UsesSStorable::UsesSStorable() = default;

/// Store UsesS Abstractions
/// \param abstractions List of abstractions
void UsesSStorable::Store(std::vector<UsesSAbstraction> abstractions) {
  for (const UsesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
