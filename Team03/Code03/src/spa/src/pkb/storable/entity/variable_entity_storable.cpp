//
// Created by kohha on 5/11/2022.
//

#include "variable_entity_storable.h"

VariableEntityStorable::VariableEntityStorable(EntityManager &entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store Variable Entities
/// \param ts List of entities
void VariableEntityStorable::Store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entity_manager_.AddVariable(entity);
  }
}