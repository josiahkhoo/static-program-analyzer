#ifndef SPA_CONSTANT_STORAGE_H
#define SPA_CONSTANT_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>

#include "common/entity/constant_entity.h"

class ConstantStorage {
public:
    ConstantStorage();

    void addConstant(ConstantEntity constant);

    std::unordered_set<std::string> getConstants();

    // Empty storage
    void clear();

private:
    static std::unordered_set<std::string> constantList;
};
#endif // SPA_CONSTANT_STORAGE_H
