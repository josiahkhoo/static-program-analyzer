#ifndef SPA_FOLLOW_PARSER_H
#define SPA_FOLLOW_PARSER_H

#include "common/clause/follows_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new FollowsClause object
class FollowsParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data) const override;
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override;
};

#endif  // SPA_FOLLOW_PARSER_H
