#ifndef QUERY_PARSER_CPP_QUERY_SELECT_PARSER_H
#define QUERY_PARSER_CPP_QUERY_SELECT_PARSER_H

#include "common/clause/select.h"
#include "query_component_parser.h"
#include "token_builder_pair.h"

/// Interface class for parsing of query operations
class QuerySelectParser : public QueryComponentParser<Select> {
 public:
  /// Converts tokens into QueryOperation object
  std::shared_ptr<Select> Parse(TokenBuilderPair data) override = 0;
};

#endif  // QUERY_PARSER_CPP_QUERY_SELECT_PARSER_H
