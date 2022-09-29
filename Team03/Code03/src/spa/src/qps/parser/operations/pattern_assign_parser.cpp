#include "pattern_assign_parser.h"

#include <cassert>

#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

bool PatternAssignParser::MatchParser(const TokenBuilderPair& data) const {
  return QueryOperationMatcher::MatchParser(data, ASSIGN);
}

std::shared_ptr<QueryOperation> PatternAssignParser::Parse(
    TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
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
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(synonym, entity_ref, exp);
  return ptn;
}
