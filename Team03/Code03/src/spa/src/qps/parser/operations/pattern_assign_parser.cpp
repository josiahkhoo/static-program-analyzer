#include "pattern_assign_parser.h"

#include <cassert>

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string PatternAssignParser::CLAUSE_WORD = "pattern";

bool PatternAssignParser::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data) const {
  return QueryOperationMatcher::MatchEntityParser(data, CLAUSE_WORD, ASSIGN);
}

std::shared_ptr<QueryOperation> PatternAssignParser::Parse(
    std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&> data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  Token next = tokens->Peek();
  tokens->Expect(Token::IDENTIFIER);
  Synonym synonym = builder.GetSynonym(next.GetValue());
  // Check if ASSIGN, IF, WHILE
  QueryParserUtil::CheckPatternSyn(synonym);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  EntityReference entity_ref =
      QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckVariableEntity(entity_ref);
  tokens->Expect(Token::COMMA);
  Expression exp;
  // ASSIGN get expression
  assert(synonym.IsEntityType(ASSIGN));
  exp = QueryParserUtil::ExtractExpression(tokens, builder);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(synonym, entity_ref, exp);
  return ptn;
}
