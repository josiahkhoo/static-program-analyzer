#ifndef SPA_QUERY_PARSER_UTIL_H
#define SPA_QUERY_PARSER_UTIL_H

#include "common/clause/follows_clause.h"
#include "common/parser.h"

/// Contains utility methods used for parsing tokens in the various *Parser
/// classes.
class QueryParserUtil {
  static StatementReference ExtractStmtRef();
  static Expression ExtractExpression();
  static std::string GetExpression();
  static std::string GetTerm();
  static void CheckFollowsParentRef(const StatementReference& stmtRef) const;
  static void CheckPatternSyn(const Synonym& synonym) const;
  static void CheckUsesLhs();
};

#endif  // SPA_QUERY_PARSER_UTIL_H
