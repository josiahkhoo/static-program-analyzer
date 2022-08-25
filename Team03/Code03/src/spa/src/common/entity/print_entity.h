//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_PRINT_ENTITY_H
#define SPA_PRINT_ENTITY_H

#include "entity.h"
#include "statement_entity.h"
#include "variable_entity.h"

class PrintEntity : public StatementEntity {
public:
  PrintEntity(int line_number, VariableEntity &variable_entity);

private:
  VariableEntity &variable_entity_;
};

#endif // SPA_PRINT_ENTITY_H
