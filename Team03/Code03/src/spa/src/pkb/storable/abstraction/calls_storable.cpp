//
// Created by kohha on 5/11/2022.
//

#include "calls_storable.h"

CallsStorable::CallsStorable() = default;

/// Store Calls Abstractions
/// \param abstractions List of abstractions
void CallsStorable::Store(std::vector<CallsAbstraction> abstractions) {
  for (const CallsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
