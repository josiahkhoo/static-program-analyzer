#include "modifies_s_parser.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string ModifiesSParser::CLAUSE_WORD = "Modifies";

bool ModifiesSParser::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  if (!QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD)) {
    return false;
  }
  // Check if ModifiesS
  return !QueryParserUtil::CheckProcedureClause(tokens, builder);
}

std::shared_ptr<QueryOperation> ModifiesSParser::Parse(
    std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  StatementReference stmtRef = QueryParserUtil::ExtractStmtRef(tokens, builder);
  // Only allow ASSIGN, READ, STATEMENT, IF, WHILE, CALL
  CheckModifiesSType(stmtRef);
  tokens->Expect(Token::COMMA);
  // Get ent
  EntityReference entRef = QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckEntityRhs(entRef);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesSClause> modCl =
      std::make_shared<ModifiesSClause>(stmtRef, entRef);
  return modCl;
}

void ModifiesSParser::CheckModifiesSType(const StatementReference& stmtRef) {
  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(READ) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
}
