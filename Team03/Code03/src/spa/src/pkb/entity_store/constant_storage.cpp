#include "constant_storage.h"

std::unordered_set<std::string> ConstantStorage::constantList;

ConstantStorage::ConstantStorage() {}

void ConstantStorage::addConstant(ConstantEntity constant) {
    constantList.emplace(std::to_string(constant.GetValue()));
}

std::unordered_set<std::string> ConstantStorage::getConstants() {
    return constantList;
}

void ConstantStorage::clear() {
    constantList.clear();
}
