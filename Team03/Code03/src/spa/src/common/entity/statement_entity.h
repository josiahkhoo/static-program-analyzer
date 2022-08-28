#ifndef SPA_STATEMENT_ENTITY_H
#define SPA_STATEMENT_ENTITY_H

#include "common/stringable.h"
#include "entity.h"

class StatementEntity : public Entity, public Stringable {
 public:
  StatementEntity(const TNode &node, int line_number);

  [[nodiscard]] int GetLineNumber() const;

  [[nodiscard]] std::string ToString() const override;

 protected:
  int line_number_;
};

#endif  // SPA_STATEMENT_ENTITY_H
