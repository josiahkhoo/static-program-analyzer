#ifndef SPA_PRINT_ENTITY_H
#define SPA_PRINT_ENTITY_H

#include "entity.h"
#include "statement_entity.h"
#include "variable_entity.h"

class PrintEntity : public StatementEntity {
 public:
  explicit PrintEntity(const TNode* node_ptr, int line_number);
};

#endif  // SPA_PRINT_ENTITY_H
