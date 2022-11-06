//
// Created by kohha on 5/11/2022.
//

#ifndef SPA_CFG_QUERYABLE_H
#define SPA_CFG_QUERYABLE_H

#include "typed_queryable.h"

class CfgQueryable : TypedQueryable {
 public:
  explicit CfgQueryable(RelationshipManager &relationship_manager_,
                        EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations() const;

  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryNextT(int statement_number,
                                                           EntityType type);

  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type);
};

#endif  // SPA_CFG_QUERYABLE_H
