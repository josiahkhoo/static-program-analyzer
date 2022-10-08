#ifndef QUERY_PARSER_CPP_NEXT_PARSER_H
#define QUERY_PARSER_CPP_NEXT_PARSER_H

#include "common/clause/next_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new NextClause object
class NextParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // QUERY_PARSER_CPP_NEXT_PARSER_H
