//
// Created by Josiah Khoo on 27/8/22.
//
#include "entity.h"

Entity::Entity(const TNode& node) : node_(node) {}

const TNode* Entity::GetNodePointer() const { return &node_; }
