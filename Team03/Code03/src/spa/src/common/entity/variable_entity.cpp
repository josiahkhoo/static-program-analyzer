#include "variable_entity.h"

#include <utility>

VariableEntity::VariableEntity(const TNode* node_ptr, std::string name)
    : Entity(node_ptr), name_(std::move(name)) {}

std::string VariableEntity::GetName() const { return name_; }
