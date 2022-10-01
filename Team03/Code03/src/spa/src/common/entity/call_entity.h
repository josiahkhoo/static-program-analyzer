#ifndef SPA_CALL_ENTITY_H
#define SPA_CALL_ENTITY_H

#include "entity.h"
#include "statement_entity.h"

class CallEntity : public StatementEntity {
 public:
  explicit CallEntity(const TNode &node, int line_number);

  [[nodiscard]] std::string GetProcedureName() const;
};

#endif  // SPA_CALL_ENTITY_H
