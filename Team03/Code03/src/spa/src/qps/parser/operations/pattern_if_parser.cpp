#include "pattern_if_parser.h"

#include <cassert>

#include "common/clause/pattern_if.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_parser_util.h"

const std::string PatternIfParser::CLAUSE_WORD = "pattern";

bool PatternIfParser::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data) const {
  return QueryOperationMatcher::MatchParser(data, CLAUSE_WORD, IF);
}

std::shared_ptr<QueryOperation> PatternIfParser::Parse(
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
  // IF get _,_
  assert(synonym.IsEntityType(IF));
  tokens->Expect(Token::UNDERSCORE);
  tokens->Expect(Token::COMMA);
  tokens->Expect(Token::UNDERSCORE);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<PatternIf> ptn =
      std::make_shared<PatternIf>(synonym, entity_ref);
  return ptn;
}
