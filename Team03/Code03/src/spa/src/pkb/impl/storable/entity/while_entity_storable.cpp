#include "while_entity_storable.h"

WhileEntityStorable::WhileEntityStorable(EntityManager& entity_manager_)
    : EntityStorable(entity_manager_) {}

/// Store While Entities
/// \param ts List of entities
void WhileEntityStorable::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}