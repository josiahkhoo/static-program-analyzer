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
  virtual ~QueryOperation() = default;

  enum Type { NO_SYNONYM, SINGLE_SYNONYM, DOUBLE_SYNONYM };

  enum IterateSide { LHS, RHS };

  /// Fetch is called when the query operation is a single synonym operation. It
  /// returns every value of the synonym associated with this clause.
  [[nodiscard]] virtual std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const = 0;

  /// FetchPossibleRhs is called when the query operation is a double synonym
  /// operation.
  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleRhs(
      std::string lhs, const QueryablePkb &queryable_pkb) const = 0;

  /// FetchPossibleLhs is called when the query operation is a double synonym
  /// operation.
  [[nodiscard]] virtual std::unordered_set<std::string> FetchPossibleLhs(
      std::string rhs, const QueryablePkb &queryable_pkb) const = 0;

  /// IsTrue is called when query operation is a no synonym operation.
  [[nodiscard]] virtual bool IsTrue(
      const QueryablePkb &queryable_pkb) const = 0;

  [[nodiscard]] virtual Type GetType() const = 0;

  [[nodiscard]] virtual Synonym GetSynonym() const = 0;

  [[nodiscard]] virtual std::pair<Synonym, Synonym> GetSynonymPair() const = 0;

  [[nodiscard]] virtual IterateSide GetIterateSide(
      std::vector<std::vector<std::string>> lhs,
      std::vector<std::vector<std::string>> rhs) const = 0;

  [[nodiscard]] bool IsRelatedTo(QueryOperation *other_op) const;
};

#endif  // SPA_QUERY_OPERATION_H
