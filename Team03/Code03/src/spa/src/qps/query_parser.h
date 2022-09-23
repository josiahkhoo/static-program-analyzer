#ifndef SPA_QUERY_PARSER_H
#define SPA_QUERY_PARSER_H

#include "common/parser.h"
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

  void ParseDeclaration();

  void ParseSelect();

  void ParseQueryOperation();

  bool ParseClause();

  void ParseIndividualClause();

  bool ParsePattern();

  void ParseCleanUpSyntax();
};

#endif  // SPA_QUERY_PARSER_H
