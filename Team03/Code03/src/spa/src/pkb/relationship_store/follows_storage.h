#ifndef SPA_FOLLOWS_STORAGE_H
#define SPA_FOLLOWS_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/abstraction/follows_abstraction.h"
#include "common/abstraction/follows_t_abstraction.h"
#include "common/abstraction/parent_abstraction.h"
#include "common/abstraction/parent_t_abstraction.h"
#include "follows_t_by_relationship.h"
#include "follows_t_relationship.h"

class FollowsStorage {
 public:
  void AddRelationship(FollowsAbstraction abstraction);

  void AddRelationship(FollowsTAbstraction abstraction);

  std::unordered_set<std::string> GetFollowsStatements() const;

  std::unordered_set<std::string> GetFollowsStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsTStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements(
      int statement_number) const;

  std::unordered_set<std::string> GetFollowsByStatements() const;

  std::unordered_set<std::string> GetFollowsTByStatements(
      int statement_number) const;

 private:
  std::unordered_map<int, int> follows_map_;
  std::unordered_map<int, int> follows_by_map_;
  std::unordered_map<int, std::unique_ptr<FollowsTRelationship>> follows_t_map_;
  std::unordered_map<int, std::unique_ptr<FollowsTByRelationship>>
      follows_t_by_map_;
};

#endif  // SPA_FOLLOWS_STORAGE_H
