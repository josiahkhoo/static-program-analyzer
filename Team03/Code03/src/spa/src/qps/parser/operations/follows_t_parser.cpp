#include "follows_t_parser.h"

#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_parser_util.h"

const std::string FollowsTParser::CLAUSE_WORD = "Follows";

bool FollowsTParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchTParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> FollowsTParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  // Starting clause word
  tokens->Expect(CLAUSE_WORD);
  tokens->Expect(Token::ASTERISK);
  tokens->Expect(Token::LEFT_ROUND_BRACKET);
  // Get stmt1
  StatementReference stmtRef1 =
      QueryParserUtil::ExtractStmtRef(tokens, builder);
  QueryParserUtil::CheckFollowsParentRef(stmtRef1);
  tokens->Expect(Token::COMMA);
  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens, builder);
  QueryParserUtil::CheckFollowsParentRef(stmtRef2);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<FollowsTClause> folCl =
      std::make_shared<FollowsTClause>(stmtRef1, stmtRef2);
  return folCl;
}
