#ifndef SPA_STATEMENT_ENTITY_H
#define SPA_STATEMENT_ENTITY_H

#include "common/stringable.h"
#include "entity.h"

class StatementEntity : public Entity, public Stringable {
 public:
  StatementEntity(const TNode &node, int statement_number_);

  [[nodiscard]] int GetStatementNumber() const;

  [[nodiscard]] std::string ToString() const override;

 protected:
  int statement_number_;
};

#endif  // SPA_STATEMENT_ENTITY_H
