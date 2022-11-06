#ifndef SPA_ENTITY_STORABLE_H
#define SPA_ENTITY_STORABLE_H

#include "pkb/entity_store/entity_manager.h"

class EntityStorable {
 protected:
  explicit EntityStorable(EntityManager &entity_manager_);
  EntityManager &entity_manager_;
};

#endif  // SPA_ENTITY_STORABLE_H
