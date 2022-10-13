#ifndef SPA_CONSTANT_STORAGE_H
#define SPA_CONSTANT_STORAGE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/constant_entity.h"

class ConstantStorage {
 public:
  ConstantStorage();

  void AddConstant(ConstantEntity constant);

  std::unordered_set<std::string> GetConstants() const;

 private:
  std::unordered_set<std::string> constantList;
};

#endif  // SPA_CONSTANT_STORAGE_H
