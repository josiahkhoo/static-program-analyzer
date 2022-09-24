#include "pattern_parser.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string PatternParser::CLAUSE_WORD = "pattern";

bool PatternParser::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> PatternParser::Parse(
    std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  // Validates if assign-entity was captured
  Token next = tokens->Peek();
  tokens->Expect(Token::IDENTIFIER);
  Synonym synonym = builder.GetSynonym(next.GetValue());
  // Check if ASSIGN, IF, WHILE
  QueryParserUtil::CheckPatternSyn(synonym);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  EntityReference entity_ref =
      QueryParserUtil::ExtractEntityRef(tokens, builder);
  if (entity_ref.IsSynonym() &&
      entity_ref.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }
  tokens->Expect(Token::COMMA);
  Expression exp;
  // ASSIGN get expression
  if (synonym.IsEntityType(ASSIGN)) {
    exp = QueryParserUtil::ExtractExpression(tokens, builder);
  }
  // IF get _,_
  else if (synonym.IsEntityType(IF)) {
    tokens->Expect(Token::UNDERSCORE);
    tokens->Expect(Token::COMMA);
    tokens->Expect(Token::UNDERSCORE);
  }
  // WHILE get _
  else if (synonym.IsEntityType(WHILE)) {
    tokens->Expect(Token::UNDERSCORE);
  }
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(synonym, entity_ref, exp);
  return ptn;
}
