//
// Created by kohha on 5/11/2022.
//

#include "calls_t_storable.h"

CallsTStorable::CallsTStorable() = default;

/// Store CallsT Abstractions
/// \param abstractions List of abstractions
void CallsTStorable::Store(std::vector<CallsTAbstraction> abstractions) {
  for (const CallsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
