//
// Created by Josiah Khoo on 27/8/22.
//
#include "entity.h"

Entity::Entity(const TNode& node) : node_(node) {}

const TNode* Entity::GetNodePointer() const { return &node_; }

bool Entity::operator==(const Entity& rhs) const { return node_ == rhs.node_; }

bool Entity::operator!=(const Entity& rhs) const { return !(rhs == *this); }
