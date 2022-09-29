#ifndef SPA_PATTERN_ASSIGN_PARSER_H
#define SPA_PATTERN_ASSIGN_PARSER_H

#include "common/clause/pattern_assign.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new Pattern ASSIGN object
class PatternAssignParser : public QueryOperationParser {
 public:
  [[nodiscard]] bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data) const override;
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override;
};

#endif  // SPA_PATTERN_ASSIGN_PARSER_H
