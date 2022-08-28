#include "constant_storage.h"

std::unordered_set<int> ConstantStorage::constantList;

ConstantStorage::ConstantStorage() {}

void ConstantStorage::addConstant(ConstantEntity constant) {
    constantList.emplace(constant.GetValue());
}

std::unordered_set<int> ConstantStorage::getConstants() {
    return constantList;
}

void ConstantStorage::clear() {
    constantList.clear();
}
