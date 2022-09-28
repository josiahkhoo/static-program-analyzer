#include "with_parser.h"

#include "common/clause/with.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string WithParser::CLAUSE_WORD = "with";

bool WithParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> WithParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  Token next = tokens->Peek();
  AttributeReference aRef1 = QueryParserUtil::ExtractAttrRef(tokens, builder);
  tokens->Expect(Token::EQUAL);
  AttributeReference aRef2 = QueryParserUtil::ExtractAttrRef(tokens, builder);
  std::shared_ptr<With> withCl = std::make_shared<With>(aRef1, aRef2);
  return withCl;
}