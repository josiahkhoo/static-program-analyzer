#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include "common/query_operator.h"
#include "common/reference/entity_reference.h"

class Select : public QueryOperator {
 public:
  explicit Select(Synonym synonym);

  [[nodiscard]] Synonym GetSynonym() const;

 private:
  Synonym synonym_;
};

#endif  // SPA_SELECT_H
