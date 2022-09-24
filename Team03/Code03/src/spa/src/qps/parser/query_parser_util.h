#ifndef SPA_QUERY_PARSER_UTIL_H
#define SPA_QUERY_PARSER_UTIL_H

#include "common/parser.h"
#include "qps/query_string_builder.h"
#include "qps/token_handler.h"

/// Contains utility methods used for parsing tokens in the various *Parser
/// classes.
class QueryParserUtil {
 public:
  static StatementReference ExtractStmtRef(
      const std::shared_ptr<TokenHandler>& tokens,
      const QueryStringBuilder& builder);
  static EntityReference ExtractEntityRef(
      const std::shared_ptr<TokenHandler>& tokens,
      const QueryStringBuilder& builder);
  static Expression ExtractExpression(
      const std::shared_ptr<TokenHandler>& tokens,
      const QueryStringBuilder& builder);
  static EntityType ExtractEntityType(
      const std::shared_ptr<TokenHandler>& tokens);

  static std::string GetExpression(const std::shared_ptr<TokenHandler>& tokens,
                                   const QueryStringBuilder& builder);
  static std::string GetTerm(const std::shared_ptr<TokenHandler>& tokens,
                             const QueryStringBuilder& builder);
  static void CheckFollowsParentRef(const StatementReference& stmtRef);
  static void CheckPatternSyn(const Synonym& synonym);
  static void CheckEntityRhs(const EntityReference& entRef);
  static void CheckProcedureEntity(const EntityReference& entRef);
  static bool CheckProcedureClause(const std::shared_ptr<TokenHandler>& tokens,
                                   const QueryStringBuilder& builder);
};

#endif  // SPA_QUERY_PARSER_UTIL_H