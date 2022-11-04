#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include <regex>

#include "token.h"
#include "vector"

class Lexer {
 public:
  std::vector<Token> Lex(std::istream &stream) const;

  std::vector<Token> LexLine(std::string &line) const;

 private:
  static void ProcessLineHead(std::string &line, std::vector<Token> &tokens);
  static void FindTokens(std::vector<Token> &tokens,
                         const std::pair<Token::Kind, std::string> &pair,
                         const std::smatch &matched_regex);
};

#endif  // SPA_LEXER_H