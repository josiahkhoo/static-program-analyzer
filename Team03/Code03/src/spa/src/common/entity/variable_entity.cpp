#include "variable_entity.h"

#include <utility>

VariableEntity::VariableEntity(const TNode &node, std::string name)
    : Entity(node), name_(std::move(name)) {}

std::string VariableEntity::GetName() const { return name_; }
