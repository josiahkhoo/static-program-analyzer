#include "pattern_while_parser.h"

#include <cassert>

#include "common/clause/pattern_while.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_parser_util.h"

bool PatternWhileParser::MatchParser(const TokenBuilderPair& data) const {
  return QueryOperationMatcher::MatchParser(data, WHILE);
}

std::shared_ptr<QueryOperation> PatternWhileParser::Parse(
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
  // WHILE get _
  assert(synonym.IsEntityType(WHILE));
  tokens->Expect(Token::UNDERSCORE);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<PatternWhile> ptn =
      std::make_shared<PatternWhile>(synonym, entity_ref);
  return ptn;
}
