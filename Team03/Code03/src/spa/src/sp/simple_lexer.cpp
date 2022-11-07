#include "simple_lexer.h"

#include <istream>

// Lexer rules specific to SP only
TokenRules SimpleLexer::token_rules_ = {{Token::WHITESPACE, "^(\\s+)"},
                         {Token::NUMBER, "^(\\d+)"},
                         {Token::IDENTIFIER, "^([a-zA-Z]+[a-zA-Z0-9]*)"},
                         {Token::LEFT_ROUND_BRACKET, "^(\\()"},
                         {Token::RIGHT_ROUND_BRACKET, "^(\\))"},
                         {Token::LEFT_CURLY_BRACKET, "^(\\{)"},
                         {Token::RIGHT_CURLY_BRACKET, "^(\\})"},
                         {Token::DOUBLE_EQUAL, "^(==)"},
                         {Token::EQUAL, "^(=)"},
                         {Token::LESS_THAN_OR_EQUAL, "^(<=)"},
                         {Token::LESS_THAN, "^(<)"},
                         {Token::GREATER_THAN_OR_EQUAL, "^(>=)"},
                         {Token::GREATER_THAN, "^(>)"},
                         {Token::PLUS, "^(\\+)"},
                         {Token::MINUS, "^(\\-)"},
                         {Token::ASTERISK, "^(\\*)"},
                         {Token::SLASH, "^(\\/)"},
                         {Token::COMMA, "^(,)"},
                         {Token::PERIOD, "^(\\.)"},
                         {Token::PERCENT, "^(%)"},
                         {Token::SEMICOLON, "^(;)"},
                         {Token::UNDERSCORE, "^(_)"},
                         {Token::OR, "^(\\|\\|)"},
                         {Token::AND, "^(&&)"},
                         {Token::NOT_EQUAL, "^(!=)"},
                         {Token::NOT, "^(!)"},
                         {Token::NEXT_LINE, "^(\n)"},
                         {Token::END, "^(\0)"}};

SimpleLexer::SimpleLexer(const Lexer &lexer) : lexer_(lexer) {}

// Splits given stream of text into a list of lines
std::vector<std::string> SimpleLexer::splitLines(std::istream &stream) {
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(stream, line)) {
    lines.push_back(line);
  }

  return lines;
}

std::vector<Token> SimpleLexer::Execute(std::istream &stream) const {
  // Generates given stream of lex into tokens
  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(stream);

  for (std::string line : lines) {
    std::vector<Token> new_tokens = lexer_.Lex(line, token_rules_);
    tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);
  return tokens;
}
