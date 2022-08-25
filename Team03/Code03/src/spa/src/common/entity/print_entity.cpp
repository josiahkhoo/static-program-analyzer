//
// Created by Josiah Khoo on 24/8/22.
//

#include "print_entity.h"
PrintEntity::PrintEntity(int line_number, VariableEntity &variable_entity)
    : StatementEntity(line_number), variable_entity_(variable_entity) {}