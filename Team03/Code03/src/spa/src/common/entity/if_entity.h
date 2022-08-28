#ifndef SPA_IF_ENTITY_H
#define SPA_IF_ENTITY_H

#include "entity.h"
#include "statement_entity.h"

class IfEntity : public StatementEntity {
 public:
  explicit IfEntity(const TNode &node, int line_number);
};

#endif  // SPA_IF_ENTITY_H
