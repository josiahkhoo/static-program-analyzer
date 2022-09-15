#ifndef SPA_QUERY_OPERATION_H
#define SPA_QUERY_OPERATION_H

#include <string>
#include <unordered_set>

#include "common/queryable_pkb.h"

class QueryOperation {
 public:
  [[nodiscard]] virtual std::unordered_set<std::string> Fetch(
      const QueryablePkb &queryable_pkb) const = 0;
  [[nodiscard]] virtual std::string GetSyn() const = 0 ;
};

#endif  // SPA_QUERY_OPERATION_H
