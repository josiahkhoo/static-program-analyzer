#ifndef SPA_QUERY_PARSER_H
#define SPA_QUERY_PARSER_H

#include "common/parser.h"
#include "query_string.h"
#include "query_string_builder.h"

class QueryParser : public Parser<QueryString> {
 public:
  QueryParser();

  QueryString Parse(std::vector<Token> tokens_) override;

 private:
  int token_pos_ = 0;
  std::vector<Token> tokens_;
  QueryStringBuilder query_string_builder_;

  Token Peek();

  bool MatchKind(Token::Kind kind);

  bool MatchString(const std::string &s);

  bool MatchStmtRef();

  bool CheckEnd();

  void Expect(Token::Kind kind);

  void Expect(const std::string &s);

  void ParseDeclaration();

  void ParseSelect();

  void ParseClause();

  void ParseFollow();

  void ParseFollowT();

  void ParsePattern();

  StatementReference ExtractStmtRef();
  EntityReference ExtractEntityRef();
  Expression ExtractExpression();
};

#endif  // SPA_QUERY_PARSER_H
