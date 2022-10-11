#include "affects_t_parser.h"

#include "qps/parser/query_parser_util.h"

const std::string AffectsTParser::CLAUSE_WORD = "Affects";

bool AffectsTParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchTParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> AffectsTParser::Parse(TokenBuilderPair data) {
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
  QueryParserUtil::CheckAffectsRef(stmtRef1);
  tokens->Expect(Token::COMMA);
  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens, builder);
  QueryParserUtil::CheckAffectsRef(stmtRef2);
  tokens->Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<AffectsTClause> affCl =
      std::make_shared<AffectsTClause>(stmtRef1, stmtRef2);
  return affCl;
}
