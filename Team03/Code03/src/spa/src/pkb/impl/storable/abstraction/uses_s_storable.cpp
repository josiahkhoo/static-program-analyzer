#include "uses_s_storable.h"

UsesSStorable::UsesSStorable(RelationshipManager& relationship_manager_)
    : RelationshipAbstractionStorable(relationship_manager_) {}

/// Store UsesS Abstractions
/// \param abstractions List of abstractions
void UsesSStorable::Store(std::vector<UsesSAbstraction> abstractions) {
  for (const UsesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
