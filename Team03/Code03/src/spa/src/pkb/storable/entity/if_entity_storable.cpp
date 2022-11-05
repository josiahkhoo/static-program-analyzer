//
// Created by kohha on 5/11/2022.
//

#include "if_entity_storable.h"

IfEntityStorable::IfEntityStorable(EntityManager &entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store If Entities
/// \param ts List of entities
void IfEntityStorable::Store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entity_manager_.AddIfStatement(entity);
  }
}