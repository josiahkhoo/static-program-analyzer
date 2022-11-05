//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_TYPED_QUERYABLE_H
#define SPA_TYPED_QUERYABLE_H

#include "pkb/entity_store/entity_manager.h"
#include "pkb/queryable/entity_queryable.h"
#include "pkb/relationship_store/relationship_manager.h"

class TypedQueryable {
 protected:
  explicit TypedQueryable(
      RelationshipManager &relationship_manager_,
      EntityQueryable &entity_queryable_);

  RelationshipManager &relationship_manager_;
  EntityQueryable &entity_queryable_;

  [[nodiscard]] std::unordered_set<std::string> FindIntersect(
      std::unordered_set<std::string> statements,
      std::unordered_set<std::string> typed_statements) const;
};

#endif  // SPA_TYPED_QUERYABLE_H
