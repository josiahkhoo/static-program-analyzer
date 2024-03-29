#ifndef SPA_MODIFIES_P_PARSER_H
#define SPA_MODIFIES_P_PARSER_H

#include "common/clause/modifies_p_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new ModifiesPClause object
class ModifiesPParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;
  static void CheckModifiesPType(const EntityReference& entRef);

 public:
  [[nodiscard]] bool MatchParser(const TokenBuilderPair& data) const override;
  std::shared_ptr<QueryOperation> Parse(TokenBuilderPair data) override;
};

#endif  // SPA_MODIFIES_P_PARSER_H
