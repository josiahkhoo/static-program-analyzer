#ifndef SPA_PARENT_PARSER_H
#define SPA_PARENT_PARSER_H

#include "common/clause/parent_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new ParentClause object
class ParentParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] static bool MatchParser(
      const std::shared_ptr<TokenHandler>& tokens);
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override;
};

#endif  // SPA_PARENT_PARSER_H
