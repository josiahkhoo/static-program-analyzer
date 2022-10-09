#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H

#include <string>
#include <unordered_set>

#include "common/entity/entity.h"
#include "common/query_operation.h"
#include "common/reference/reference.h"

class Clause : public QueryOperation {
 public:
  virtual ~Clause() = default;

  [[nodiscard]] virtual const Reference &GetLeftHandSide() const = 0;

  [[nodiscard]] virtual const Reference &GetRightHandSide() const = 0;

  [[nodiscard]] Synonym GetSynonym() const override;

  [[nodiscard]] std::pair<Synonym, Synonym> GetSynonymPair() const override;

  [[nodiscard]] Type GetType() const override;

  [[nodiscard]] IterateSide GetIterateSide(
      std::vector<std::vector<std::string>> lhs,
      std::vector<std::vector<std::string>> rhs) const override;

  [[nodiscard]] std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const override;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchRhs(
      const QueryablePkb &queryable_pkb) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchLhs(
      const QueryablePkb &queryable_pkb) const = 0;
};

#endif  // SPA_CLAUSE_H
