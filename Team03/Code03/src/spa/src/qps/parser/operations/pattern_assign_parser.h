#ifndef SPA_PATTERN_ASSIGN_PARSER_H
#define SPA_PATTERN_ASSIGN_PARSER_H

#include "common/clause/pattern_assign.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new Pattern ASSIGN object
class PatternAssignParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_PATTERN_ASSIGN_PARSER_H
