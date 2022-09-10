#ifndef SPA_ASSIGN_PATTERN_STORAGE_H
#define SPA_ASSIGN_PATTERN_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/assign_entity.h"

class AssignPatternStorage {
 public:
  void AddAssignPattern(AssignEntity assignEntity);

  void Clear();

 private:
  static std::unordered_map<int, std::pair<std::string, std::string>>
      patterns_map_;
};

#endif  // SPA_ASSIGN_PATTERN_STORAGE_H
