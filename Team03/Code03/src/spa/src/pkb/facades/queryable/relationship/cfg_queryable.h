#ifndef SPA_CFG_QUERYABLE_H
#define SPA_CFG_QUERYABLE_H

#include "pkb/facades/queryable/queryable_utility.h"

class CfgQueryable {
 public:
  explicit CfgQueryable(const RelationshipManager &relationship_manager_,
                        const EntityQueryable &entity_queryable_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations() const;

  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryNextT(
      int statement_number, EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int statement_number, EntityType type) const;

 private:
  const RelationshipManager &relationship_manager_;
  const EntityQueryable &entity_queryable_;
};

#endif  // SPA_CFG_QUERYABLE_H
