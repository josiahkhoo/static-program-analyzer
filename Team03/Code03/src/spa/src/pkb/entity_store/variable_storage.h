#ifndef SPA_VARIABLE_STORAGE_H
#define SPA_VARIABLE_STORAGE_H

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/entity/variable_entity.h"

class VariableStorage {
public:
    VariableStorage();

    void addVariable(VariableEntity variable);

    std::unordered_set<std::string> getVariables();

    // Empty storage
    void clear();

private:
    static std::unordered_set<std::string> variableList;
};

#endif // SPA_VARIABLE_STORAGE_H
