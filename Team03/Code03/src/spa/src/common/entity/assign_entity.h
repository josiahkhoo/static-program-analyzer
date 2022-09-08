#ifndef SPA_ASSIGN_ENTITY_H
#define SPA_ASSIGN_ENTITY_H

#include "entity.h"
#include "pattern_statement_entity.h"

class AssignEntity : public PatternStatementEntity {
 public:
  explicit AssignEntity(const TNode &node, int line_number);
};

#endif  // SPA_ASSIGN_ENTITY_H
