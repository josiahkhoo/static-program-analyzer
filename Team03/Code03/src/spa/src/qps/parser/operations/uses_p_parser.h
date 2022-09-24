#ifndef SPA_USES_P_PARSER_H
#define SPA_USES_P_PARSER_H

#include "common/clause/uses_p_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new UsesSClause object
class UsesPParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;
  static void CheckUsesPType(const EntityReference& entRef);

 public:
  [[nodiscard]] bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data) const override;
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override;
};

#endif  // SPA_USES_P_PARSER_H
