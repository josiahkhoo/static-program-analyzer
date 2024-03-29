#ifndef SPA_QUERY_PARSER_UTIL_H
#define SPA_QUERY_PARSER_UTIL_H

#include "common/parser.h"
#include "common/reference/attribute_name.h"
#include "common/reference/attribute_reference.h"
#include "common/reference/identifier.h"
#include "common/reference/integer.h"
#include "common/token_handler.h"
#include "qps/query_string_builder.h"

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
  static AttributeReference ExtractAttrRef(
      const std::shared_ptr<TokenHandler>& tokens,
      const QueryStringBuilder& builder);
  static AttributeName ExtractAttrName(
      Synonym synonym, const std::shared_ptr<TokenHandler>& tokens);
  static void CheckFollowsParentRef(const StatementReference& stmtRef);
  static void CheckStatementTypeRef(const StatementReference& stmtRef);
  static void CheckPatternSyn(const Synonym& synonym);
  static void CheckProcedureEntity(const EntityReference& entRef);
  static void CheckVariableEntity(const EntityReference& entRef);
  static bool CheckProcedureClause(const std::shared_ptr<TokenHandler>& tokens,
                                   const QueryStringBuilder& builder);
  static Synonym ExtractSynonym(const QueryStringBuilder& builder,
                                const Identifier& identifier);

 private:
  static std::string GetExpression(const std::shared_ptr<TokenHandler>& tokens,
                                   const QueryStringBuilder& builder);

  static std::string GetTerm(const std::shared_ptr<TokenHandler>& tokens,
                             const QueryStringBuilder& builder);

  static Identifier ExtractIdentifier(
      const std::shared_ptr<TokenHandler>& tokens);
  static Integer ExtractInteger(const std::shared_ptr<TokenHandler>& tokens);
  static Expression CreateExpression(
      std::optional<Expression>& maybe_expression, int wildcard_found);
};

#endif  // SPA_QUERY_PARSER_UTIL_H
