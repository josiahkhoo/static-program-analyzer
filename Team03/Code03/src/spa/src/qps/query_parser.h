#ifndef SPA_QUERY_PARSER_H
#define SPA_QUERY_PARSER_H

#include "common/parser.h"
#include "query_string.h"
#include "query_string_builder.h"
#include "token_handler.h"

class QueryParser : public Parser<QueryString> {
 public:
  QueryParser();

  QueryString Parse(std::vector<Token> tokens_) override;

 private:
  TokenHandler tokens_;
  QueryStringBuilder query_string_builder_;

  void ParseDeclaration();

  void ParseSelect();

  bool ParseClause();

  void ParseFollows();

  void ParseFollowsT();

  void ParseParent();

  void ParseParentT();

  void ParseUses();

  void ParseUsesS();

  void ParseUsesP();

  void ParseModifies();

  void ParseModifiesS();

  void ParseModifiesP();

  void ParseCalls();

  void ParseCallsT();

  bool ParsePattern();

  void ParseQueryOperation();

  void ParseCleanUpSyntax();
  void CheckUsesLhs(TokenHandler tokens, const QueryStringBuilder& builder);
  void CheckModifiesLhs(TokenHandler tokens, const QueryStringBuilder& builder);
};

#endif  // SPA_QUERY_PARSER_H
