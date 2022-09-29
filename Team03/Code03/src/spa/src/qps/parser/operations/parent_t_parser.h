#ifndef SPA_PARENT_T_PARSER_H
#define SPA_PARENT_T_PARSER_H

#include "common/clause/parent_t_clause.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new ParentTClause object
class ParentTParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_PARENT_T_PARSER_H
