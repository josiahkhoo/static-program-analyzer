//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_ENTITY_QUERYABLE_H
#define SPA_ENTITY_QUERYABLE_H

#include "common/entity/entity_type.h"
#include "pkb/entity_store/entity_manager.h"

class EntityQueryable {
 public:
  explicit EntityQueryable(EntityManager &entity_manager_);
  [[nodiscard]] std::unordered_set<std::string> QueryAll(EntityType type) const;
 protected:
  EntityManager &entity_manager_;
};

#endif  // SPA_ENTITY_QUERYABLE_H
