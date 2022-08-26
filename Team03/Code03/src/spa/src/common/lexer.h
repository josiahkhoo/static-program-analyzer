#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include "token.h"
#include "vector"

class Lexer {
 public:
  virtual std::vector<Token> lex(std::istream &stream) = 0;
};

#endif  // SPA_LEXER_H
