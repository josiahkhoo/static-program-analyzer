#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include "common/entity/entity.h"
#include "common/query_operator.h"
#include "common/reference/reference.h"

class Clause : public QueryOperator {
 public:
  explicit Clause(Reference lhs, Reference rhs);
  [[nodiscard]] const Reference &GetLeftHandSide() const;
  [[nodiscard]] const Reference &GetRightHandSide() const;

 private:
  Reference lhs_;

 public:
  bool operator==(const Clause &rhs) const;
  bool operator!=(const Clause &rhs) const;

 private:
  Reference rhs_;
};

#endif  // SPA_CLAUSE_H
