#ifndef SPA_CALLS_QUERYABLE_H
#define SPA_CALLS_QUERYABLE_H

#include "pkb/relationship_store/relationship_manager.h"

class CallsQueryable {
 public:
  explicit CallsQueryable(const RelationshipManager &relationship_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls() const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy() const;

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations() const;

  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string identifier) const;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string identifier) const;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string identifier) const;

  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string identifier) const;

 private:
  const RelationshipManager &relationship_manager_;
};

#endif  // SPA_CALLS_QUERYABLE_H
