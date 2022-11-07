#ifndef SPA_SIMPLE_LEXER_H
#define SPA_SIMPLE_LEXER_H

#include "common/lexer.h"

class SimpleLexer {
 public:
  explicit SimpleLexer(const Lexer &lexer);

  std::vector<Token> Execute(std::istream &stream) const;

 private:
  const Lexer &lexer_;
  static std::vector<std::string> ConvertStreamToLines(std::istream &stream);
  static TokenRules token_rules_;
};

#endif  // SPA_SIMPLE_LEXER_H
