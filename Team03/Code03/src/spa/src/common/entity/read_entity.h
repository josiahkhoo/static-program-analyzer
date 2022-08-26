#ifndef SPA_READ_ENTITY_H
#define SPA_READ_ENTITY_H

#include "entity.h"
#include "statement_entity.h"
#include "variable_entity.h"

class ReadEntity : public StatementEntity {
 public:
  explicit ReadEntity(const TNode* node_ptr, int line_number);
};

#endif  // SPA_READ_ENTITY_H
