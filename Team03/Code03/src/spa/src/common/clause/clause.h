#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <string>
#include <unordered_set>

#include "common/entity/entity.h"
#include "common/query_operator.h"
#include "common/queryable_pkb.h"
#include "common/reference/reference.h"

class Clause : public QueryOperator {
 public:
  [[nodiscard]] virtual const Reference &GetLeftHandSide() const = 0;

  [[nodiscard]] virtual const Reference &GetRightHandSide() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const = 0;
};

#endif  // SPA_CLAUSE_H
