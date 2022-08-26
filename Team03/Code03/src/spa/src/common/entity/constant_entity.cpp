#include "constant_entity.h"

ConstantEntity::ConstantEntity(const TNode* node_ptr, int value)
    : Entity(node_ptr), value_(value) {}

int ConstantEntity::GetValue() const { return value_; }
