#ifndef SPA_QUERY_LEXER_H
#define SPA_QUERY_LEXER_H

#include "common/lexer.h"

class QueryLexer {
 public:
  explicit QueryLexer(const Lexer &lexer);

  std::vector<Token> Execute(std::string &query) const;

 private:
  const Lexer &lexer_;
  static TokenRules token_rules_;
};

#endif  // SPA_QUERY_LEXER_H
