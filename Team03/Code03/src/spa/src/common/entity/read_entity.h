#ifndef SPA_READ_ENTITY_H
#define SPA_READ_ENTITY_H

#include "entity.h"
#include "statement_entity.h"
#include "variable_entity.h"

class ReadEntity : public StatementEntity {
 public:
  ReadEntity(int line_number, VariableEntity variable_entity);

 private:
  VariableEntity variable_entity_;
};

#endif  // SPA_READ_ENTITY_H
