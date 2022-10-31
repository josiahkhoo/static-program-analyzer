#ifndef SPA_QUERY_OPERATION_PARSER_H
#define SPA_QUERY_OPERATION_PARSER_H

#include "common/parser.h"
#include "common/token_handler.h"
#include "qps/parser/token_builder_pair.h"
#include "qps/query_string_builder.h"
#include "query_component_parser.h"

/// Interface class for parsing of query operations
class QueryOperationParser : public QueryComponentParser<QueryOperation> {
 public:
  virtual ~QueryOperationParser() = default;
  /// Converts tokens into QueryOperation object
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override = 0;
};

#endif  // SPA_QUERY_OPERATION_PARSER_H
