#ifndef SPA_QUERYABLE_UTILITY_H
#define SPA_QUERYABLE_UTILITY_H

#include "pkb/facades/queryable/entity_queryable.h"
#include "pkb/relationship_store/relationship_manager.h"

class QueryableUtility {
 public:
  [[nodiscard]] static std::unordered_set<std::string> FindIntersect(
      std::unordered_set<std::string> statements,
      std::unordered_set<std::string> typed_statements);
};

#endif  // SPA_QUERYABLE_UTILITY_H
