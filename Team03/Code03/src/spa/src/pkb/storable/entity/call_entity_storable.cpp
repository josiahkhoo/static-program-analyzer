//
// Created by kohha on 5/11/2022.
//

#include "call_entity_storable.h"

CallEntityStorable::CallEntityStorable(EntityManager &entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store Call Entities
/// \param ts List of entities
void CallEntityStorable::Store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entity_manager_.AddCallStatement(entity);
  }
}