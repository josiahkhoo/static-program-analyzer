#include "calls_t_storable.h"

CallsTStorable::CallsTStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store CallsT Abstractions
/// \param abstractions List of abstractions
void CallsTStorable::Store(std::vector<CallsTAbstraction> abstractions) {
  for (const CallsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
