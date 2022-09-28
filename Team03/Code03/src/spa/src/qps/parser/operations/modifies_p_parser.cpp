#include "modifies_p_parser.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string ModifiesPParser::CLAUSE_WORD = "Modifies";

bool ModifiesPParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  if (!QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD)) {
    return false;
  }
  // Check if ModifiesP
  return QueryParserUtil::CheckProcedureClause(tokens, builder);
}

std::shared_ptr<QueryOperation> ModifiesPParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  EntityReference entRef1 = QueryParserUtil::ExtractEntityRef(tokens, builder);
  // Only allow PROCEDURE
  CheckModifiesPType(entRef1);
  tokens->Expect(Token::COMMA);
  // Get ent2
  EntityReference entRef2 = QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckEntityRhs(entRef2);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesPClause> modCl =
      std::make_shared<ModifiesPClause>(entRef1, entRef2);
  return modCl;
}

void ModifiesPParser::CheckModifiesPType(const EntityReference& entRef) {
  if (!(entRef.IsIdentifier() || entRef.IsEntityType(PROCEDURE))) {
    throw SemanticException("tokens_->Expected identifier entity reference");
  }
}
