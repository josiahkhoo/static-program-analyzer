#ifndef SPA_QUERY_OPERATION_PARSER_H
#define SPA_QUERY_OPERATION_PARSER_H

#include "common/clause/pattern.h"
#include "common/parser.h"
#include "qps/query_string_builder.h"
#include "qps/token_handler.h"

/// Interface class for parsing of query operations
class QueryOperationParser
    : public Parser<
          std::shared_ptr<QueryOperation>,
          std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>> {
 public:
  /// Checks if tokens match grammar rules of QueryOperation object
  [[nodiscard]] virtual bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data) const = 0;
  /// Converts tokens into QueryOperation object
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override = 0;
};

#endif  // SPA_QUERY_OPERATION_PARSER_H
