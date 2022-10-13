#include "constant_storage.h"

ConstantStorage::ConstantStorage() {}

void ConstantStorage::AddConstant(ConstantEntity constant) {
  constantList.emplace(std::to_string(constant.GetValue()));
}

std::unordered_set<std::string> ConstantStorage::GetConstants() const {
  return constantList;
}
