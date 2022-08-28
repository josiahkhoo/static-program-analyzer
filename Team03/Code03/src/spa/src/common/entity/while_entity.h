#ifndef SPA_WHILE_ENTITY_H
#define SPA_WHILE_ENTITY_H

#include "statement_entity.h"

class WhileEntity : public StatementEntity {
 public:
  explicit WhileEntity(const TNode &node, int line_number_);
};

#endif  // SPA_WHILE_ENTITY_H
