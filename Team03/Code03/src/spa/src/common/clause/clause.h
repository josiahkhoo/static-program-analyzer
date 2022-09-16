#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <string>
#include <unordered_set>

#include "common/entity/entity.h"
#include "common/query_operation.h"
#include "common/reference/reference.h"

class Clause : public QueryOperation {
 public:
  [[nodiscard]] virtual const Reference &GetLeftHandSide() const = 0;

  [[nodiscard]] virtual const Reference &GetRightHandSide() const = 0;

  [[nodiscard]] Synonym GetSynonym() const override;

  [[nodiscard]] std::pair<Synonym, Synonym> GetSynonymPair() const override;

  [[nodiscard]] Type GetType() const override;
};

#endif  // SPA_CLAUSE_H
