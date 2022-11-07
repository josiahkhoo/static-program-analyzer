#ifndef SPA_LEXER_H
#define SPA_LEXER_H

#include <regex>

#include "token.h"
#include "vector"

typedef std::vector<std::pair<Token::Kind, std::string>> TokenRules;

class Lexer {
 public:
  std::vector<Token> Lex(std::string &line, TokenRules &token_rules) const;

 private:
  static void ProcessLineHead(std::string &line, std::vector<Token> &tokens,
                       TokenRules &token_rules);
  static void FindTokens(std::vector<Token> &tokens,
                         const std::pair<Token::Kind, std::string> &pair,
                         const std::smatch &matched_regex);
};

#endif  // SPA_LEXER_H