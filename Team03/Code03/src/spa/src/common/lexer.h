#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include <regex>

#include "token.h"
#include "vector"

class Lexer {
 public:
  std::vector<Token> Lex(
      std::istream &stream,
      std::vector<std::pair<Token::Kind, std::string>> &token_rules) const;

  std::vector<Token> LexLine(
      std::string &line,
      std::vector<std::pair<Token::Kind, std::string>> &token_rules) const;

 private:
  static void ProcessLineHead(
      std::string &line, std::vector<Token> &tokens,
      std::vector<std::pair<Token::Kind, std::string>> &token_rules);
  static void FindTokens(std::vector<Token> &tokens,
                         const std::pair<Token::Kind, std::string> &pair,
                         const std::smatch &matched_regex);
};

#endif  // SPA_LEXER_H