#include "constant_storage.h"

std::unordered_set<std::string> ConstantStorage::constantList;

ConstantStorage::ConstantStorage() {}

void ConstantStorage::AddConstant(ConstantEntity constant) {
  constantList.emplace(std::to_string(constant.GetValue()));
}

std::unordered_set<std::string> ConstantStorage::GetConstants() {
  return constantList;
}

void ConstantStorage::Clear() { constantList.clear(); }
