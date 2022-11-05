//
// Created by kohha on 5/11/2022.
//

#include "read_entity_storable.h"

ReadEntityStorable::ReadEntityStorable() = default;

/// Store Read Entities
/// \param ts List of entities
void ReadEntityStorable::Store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entity_manager_.AddReadStatement(entity);
  }
}