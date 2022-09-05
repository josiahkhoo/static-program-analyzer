#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include "token.h"
#include "vector"

class Lexer {
 public:
  std::vector<Token> Lex(std::istream &stream) const;

  std::vector<Token> LexLine(std::string &line) const;
};

#endif  // SPA_LEXER_H