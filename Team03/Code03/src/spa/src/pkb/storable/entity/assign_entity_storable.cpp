//
// Created by kohha on 5/11/2022.
//

#include "assign_entity_storable.h"

#include <utility>

AssignEntityStorable::AssignEntityStorable(EntityManager &entity_manager_,
                                           PatternManager &pattern_manager_)
    : EntityStorable(entity_manager_),
      pattern_manager_(pattern_manager_) {}

/// Store Assign Entities
/// \param ts List of entities
void AssignEntityStorable::Store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entity_manager_.AddAssignStatement(entity);
    pattern_manager_.AddAssignPattern(entity);
  }
}
