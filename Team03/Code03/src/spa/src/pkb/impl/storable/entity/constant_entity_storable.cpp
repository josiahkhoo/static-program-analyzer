#include "constant_entity_storable.h"

ConstantEntityStorable::ConstantEntityStorable(EntityManager& entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store Constant Entities
/// \param ts List of entities
void ConstantEntityStorable::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}
