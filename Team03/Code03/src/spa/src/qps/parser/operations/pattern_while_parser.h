#ifndef SPA_PATTERN_WHILE_PARSER_H
#define SPA_PATTERN_WHILE_PARSER_H

#include "common/clause/pattern_assign.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new Pattern WHILE object
class PatternWhileParser : public QueryOperationParser {
 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_PATTERN_WHILE_PARSER_H
