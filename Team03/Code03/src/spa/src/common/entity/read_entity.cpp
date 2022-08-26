//
// Created by Josiah Khoo on 24/8/22.
//

#include "read_entity.h"

ReadEntity::ReadEntity(int line_number, VariableEntity variable_entity)
    : StatementEntity(line_number), variable_entity_(variable_entity) {}
