//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_STATEMENT_ENTITY_H
#define SPA_STATEMENT_ENTITY_H

#include "entity.h"

class StatementEntity : public Entity, public Stringable {
 public:
  explicit StatementEntity(int line_number);

  int GetLineNumber() const;

  std::string ToString() const override;

 protected:
  int line_number_;
};

#endif  // SPA_STATEMENT_ENTITY_H
