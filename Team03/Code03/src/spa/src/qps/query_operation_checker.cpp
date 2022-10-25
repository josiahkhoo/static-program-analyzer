#include "query_operation_checker.h"

#include "common/clause/affects_clause.h"
#include "qps/exceptions/semantic_exception.h"

QueryOperationChecker::QueryOperationChecker() = default;

void QueryOperationChecker::Check(const QueryString &q_string,
                                  const QueryablePkb &queryable_pkb) {
  for (const auto &query_operation : q_string.GetQueryOperation()) {
    if (!query_operation->IsValid(queryable_pkb)) {
      throw SemanticException("Invalid query operation parameters");
    }
  }
}
