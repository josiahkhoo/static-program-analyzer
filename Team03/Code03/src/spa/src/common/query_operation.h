#ifndef SPA_QUERY_OPERATION_H
#define SPA_QUERY_OPERATION_H

#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include "common/queryable_pkb.h"
#include "common/reference/synonym.h"

class QueryOperation {
 public:
  enum Type { NO_SYNONYM, SINGLE_SYNONYM, DOUBLE_SYNONYM };

  enum IterateSide { LHS, RHS };

  [[nodiscard]] virtual std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const = 0;
  [[nodiscard]] virtual Type GetType() const = 0;

  [[nodiscard]] virtual Synonym GetSynonym() const = 0;

  [[nodiscard]] virtual std::pair<Synonym, Synonym> GetSynonymPair() const = 0;

  [[nodiscard]] virtual IterateSide GetIterateSide(
      std::vector<std::vector<std::string>> lhs,
      std::vector<std::vector<std::string>> rhs) const = 0;
};

#endif  // SPA_QUERY_OPERATION_H
