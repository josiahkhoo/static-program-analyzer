#ifndef QUERY_PARSER_CPP_QUERY_COMPONENT_PARSER_H
#define QUERY_PARSER_CPP_QUERY_COMPONENT_PARSER_H

#include "common/parser.h"
#include "token_builder_pair.h"

template <class T>
class QueryComponentParser
    : public Parser<std::shared_ptr<T>, TokenBuilderPair> {
 public:
  /// Checks if tokens match grammar rules
  [[nodiscard]] virtual bool MatchParser(
      const TokenBuilderPair& data) const = 0;
  std::shared_ptr<T> Parse(TokenBuilderPair data) override = 0;
};

#endif  // QUERY_PARSER_CPP_QUERY_COMPONENT_PARSER_H
