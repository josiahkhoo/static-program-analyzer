#ifndef QUERY_PARSER_CPP_AFFECTS_T_PARSER_H
#define QUERY_PARSER_CPP_AFFECTS_T_PARSER_H

#include "common/clause/affects_t_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new AffectsTClause object
class AffectsTParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // QUERY_PARSER_CPP_AFFECTS_T_PARSER_H
