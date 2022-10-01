#ifndef SPA_QUERY_PARSER_H
#define SPA_QUERY_PARSER_H

#include "common/parser.h"
#include "qps/parser/query_operation_parser.h"
#include "qps/query_string.h"
#include "qps/query_string_builder.h"
#include "qps/token_handler.h"

class QueryParser : public Parser<QueryString, std::vector<Token>> {
 public:
  QueryParser();

  QueryString Parse(std::vector<Token> tokens_) override;

 private:
  std::shared_ptr<TokenHandler> tokens_;
  QueryStringBuilder query_string_builder_;
  std::vector<std::shared_ptr<QueryOperationParser>> st_parsers_;
  std::vector<std::shared_ptr<QueryOperationParser>> pattern_parsers_;
  Token last_query_operation_ = Token(Token::Kind::WHITESPACE);

  void ParseDeclaration();

  void ParseSelect();

  void ParseQueryOperation();

  bool CheckClauseKeyWord(bool isAnd, const std::string& s);

  bool ParseClause(bool isAnd = false);

  void ParseIndividualClause();

  bool ParsePattern(bool isAnd = false);

  bool ParseWith(bool isAnd = false);

  void CheckLeftoverTokens();
};

#endif  // SPA_QUERY_PARSER_H
