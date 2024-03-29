#include "parent_t_parser.h"

#include "qps/parser/query_operation_matcher.h"
#include "qps/parser/query_parser_util.h"

const std::string ParentTParser::CLAUSE_WORD = "Parent";

bool ParentTParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchTParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> ParentTParser::Parse(TokenBuilderPair data) {
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
  std::shared_ptr<ParentTClause> parCl =
      std::make_shared<ParentTClause>(stmtRef1, stmtRef2);
  return parCl;
}
