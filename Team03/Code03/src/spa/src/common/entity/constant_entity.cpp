#include "constant_entity.h"

ConstantEntity::ConstantEntity(const TNode &node, int value)
    : Entity(node), value_(value) {}

int ConstantEntity::GetValue() const { return value_; }
