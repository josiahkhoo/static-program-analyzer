#ifndef SPA_PATTERN_MANAGER_H
#define SPA_PATTERN_MANAGER_H

#include <string>
#include <vector>

#include "assign_pattern_storage.h"
#include "common/entity/assign_entity.h"

class PatternManager {
 public:
  PatternManager();

  void AddAssignPattern(AssignEntity statement);

  void Clear();

 private:
  static AssignPatternStorage assign_pattern_storage_;
};

#endif  // SPA_PATTERN_MANAGER_H
