#include "uses_s_parser.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string UsesSParser::CLAUSE_WORD = "Uses";

bool UsesSParser::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  if (!QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD)) {
    return false;
  }
  // Check if UsesS
  return !QueryParserUtil::CheckProcedureClause(tokens, builder);
}

std::shared_ptr<QueryOperation> UsesSParser::Parse(
    std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  StatementReference stmtRef = QueryParserUtil::ExtractStmtRef(tokens, builder);
  // Only allow ASSIGN, PRINT, STATEMENT, IF, WHILE, CALL
  CheckUsesSType(stmtRef);
  tokens->Expect(Token::COMMA);
  // Get ent
  EntityReference entRef = QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckEntityRhs(entRef);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesSClause> usesCl =
      std::make_shared<UsesSClause>(stmtRef, entRef);
  return usesCl;
}

void UsesSParser::CheckUsesSType(const StatementReference& stmtRef) {
  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(PRINT) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
}
