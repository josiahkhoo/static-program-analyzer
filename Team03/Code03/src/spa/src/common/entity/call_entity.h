#ifndef SPA_CALL_ENTITY_H
#define SPA_CALL_ENTITY_H

#include "entity.h"
#include "statement_entity.h"

class CallEntity : public StatementEntity {
 public:
  explicit CallEntity(const TNode* node_ptr, int line_number);
};

#endif  // SPA_CALL_ENTITY_H
