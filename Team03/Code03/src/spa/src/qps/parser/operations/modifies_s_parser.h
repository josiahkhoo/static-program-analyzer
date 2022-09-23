#ifndef SPA_MODIFIES_S_PARSER_H
#define SPA_MODIFIES_S_PARSER_H

#include "common/clause/modifies_s_clause.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_operation_parser.h"

/// Parser tokens and creates a new ModifiesSClause object
class ModifiesSParser : public QueryOperationParser {
 private:
  static const std::string CLAUSE_WORD;
  static void CheckModifiesSType(const StatementReference& stmtRef);

 public:
  [[nodiscard]] static bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data);
  std::shared_ptr<QueryOperation> Parse(
      std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data)
      override;
};

#endif  // SPA_MODIFIES_S_PARSER_H
