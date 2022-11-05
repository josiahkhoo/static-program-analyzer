//
// Created by kohha on 5/11/2022.
//

#include "constant_entity_storable.h"

ConstantEntityStorable::ConstantEntityStorable() = default;

/// Store Constant Entities
/// \param ts List of entities
void ConstantEntityStorable::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}
