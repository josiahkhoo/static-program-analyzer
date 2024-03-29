#include "calls_parser.h"

#include "qps/parser/query_parser_util.h"

const std::string CallsParser::CLAUSE_WORD = "Calls";

bool CallsParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> CallsParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  // Get stmt1
  EntityReference entRef1 = QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckProcedureEntity(entRef1);
  tokens->Expect(Token::COMMA);
  // Get stmt2
  EntityReference entRef2 = QueryParserUtil::ExtractEntityRef(tokens, builder);
  QueryParserUtil::CheckProcedureEntity(entRef2);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<CallsClause> callsCl =
      std::make_shared<CallsClause>(entRef1, entRef2);
  return callsCl;
}
