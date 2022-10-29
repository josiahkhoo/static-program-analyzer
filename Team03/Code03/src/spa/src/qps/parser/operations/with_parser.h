#ifndef SPA_WITH_PARSER_H
#define SPA_WITH_PARSER_H
#include "common/clause/uses_s_clause.h"
#include "common/parser.h"
#include "common/reference/attribute_reference.h"
#include "common/reference/identifier.h"
#include "common/token_handler.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"
#include "qps/query_string_builder.h"

/// Parser tokens and creates a new With object
class WithParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_WITH_PARSER_H
