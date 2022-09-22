#ifndef SPA_QUERY_PARSER_UTIL_H
#define SPA_QUERY_PARSER_UTIL_H

#include "common/parser.h"
#include "query_string_builder.h"
#include "token_handler.h"

/// Contains utility methods used for parsing tokens in the various *Parser
/// classes.
class QueryParserUtil {
 public:
  static StatementReference ExtractStmtRef(TokenHandler& tokens,
                                           const QueryStringBuilder& builder);
  static EntityReference ExtractEntityRef(TokenHandler& tokens,
                                          const QueryStringBuilder& builder);
  static Expression ExtractExpression(TokenHandler& tokens,
                                      const QueryStringBuilder& builder);
  static EntityType ExtractEntityType(TokenHandler& tokens);

  static std::string GetExpression(TokenHandler& tokens,
                                   const QueryStringBuilder& builder);
  static std::string GetTerm(TokenHandler& tokens,
                             const QueryStringBuilder& builder);
  static void CheckFollowsParentRef(const StatementReference& stmtRef);
  static void CheckPatternSyn(const Synonym& synonym);
//  static void CheckUsesLhs(TokenHandler& tokens,
//                           const QueryStringBuilder& builder);
  static void CheckEntityRhs(const EntityReference& entRef);
//  static void CheckModifiesLhs(TokenHandler& tokens,
//                               const QueryStringBuilder& builder);
  static void CheckProcedureEntity(const EntityReference& entRef);
};

#endif  // SPA_QUERY_PARSER_UTIL_H
