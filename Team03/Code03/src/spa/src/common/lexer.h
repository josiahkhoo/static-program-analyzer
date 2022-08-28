#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include "token.h"
#include "vector"

class Lexer {
 public:
  static std::vector<Token> lex(std::istream &stream);
};

#endif  // SPA_LEXER_H