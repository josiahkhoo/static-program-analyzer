#ifndef SPA_FOLLOWS_STORAGE_H
#define SPA_FOLLOWS_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/constant_entity.h"

class FollowsStorage {
public:
  FollowsStorage();

  // TO CHANGE ConstantEntity TO A CUSTOM STRUCT
  void AddFollowsRelationship(ConstantEntity constant);

  std::unordered_set<std::string> GetConstants();

  // Empty storage
  void Clear();

private:
  static std::unordered_set<std::string> constantList;
};

#endif  // SPA_FOLLOWS_STORAGE_H
