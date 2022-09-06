#ifndef SPA_FOLLOWS_STORAGE_H
#define SPA_FOLLOWS_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/abstraction/follows_abstraction.h"
#include "follows_relationship.h"

class FollowsStorage {
public:
  FollowsStorage();

  void AddFollowsRelationship(FollowsAbstraction followsAbs);

  std::unordered_map<int, FollowsRelationship*> GetFollows();

  // Empty storage
  void Clear();

private:
  static std::unordered_map<int, FollowsRelationship*> followsMap;
};

#endif  // SPA_FOLLOWS_STORAGE_H
