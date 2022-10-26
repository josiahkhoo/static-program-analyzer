#ifndef QUERY_PARSER_CPP_QUERY_OPERATION_CHECKER_H
#define QUERY_PARSER_CPP_QUERY_OPERATION_CHECKER_H

#include "common/queryable_pkb.h"
#include "query_string.h"

class QueryOperationChecker {
 public:
  QueryOperationChecker();

  static void Check(const QueryString &q_string,
                    const QueryablePkb &queryable_pkb);
};

#endif  // QUERY_PARSER_CPP_QUERY_OPERATION_CHECKER_H
