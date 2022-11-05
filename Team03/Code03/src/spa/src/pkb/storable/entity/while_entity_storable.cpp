//
// Created by kohha on 5/11/2022.
//

#include "while_entity_storable.h"

WhileEntityStorable::WhileEntityStorable() = default;

/// Store While Entities
/// \param ts List of entities
void WhileEntityStorable::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}