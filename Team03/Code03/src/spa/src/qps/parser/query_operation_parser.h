#ifndef SPA_QUERY_OPERATION_PARSER_H
#define SPA_QUERY_OPERATION_PARSER_H

#include "common/parser.h"
#include "qps/parser/token_builder_pair.h"
#include "qps/query_string_builder.h"
#include "qps/token_handler.h"

/// Interface class for parsing of query operations
class QueryOperationParser
    : public Parser<std::shared_ptr<QueryOperation>, TokenBuilderPair> {
 public:
  /// Checks if tokens match grammar rules of QueryOperation object
  [[nodiscard]] virtual bool MatchParser(
      const TokenBuilderPair& data) const = 0;
  /// Converts tokens into QueryOperation object
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override = 0;
};

#endif  // SPA_QUERY_OPERATION_PARSER_H
