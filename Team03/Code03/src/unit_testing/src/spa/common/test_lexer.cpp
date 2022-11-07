#include <sstream>

#include "catch.hpp"
#include "common/lexer.h"
#include "common/token.h"
#include "vector"

std::vector<std::string> splitLines(std::istream &stream) {
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
}

TEST_CASE("Extract all string tokens", "[Lexer]") {
  std::istringstream str_stream(
      "1\nh1\n(\n)\n{\n}\n==\n=\n<=\n<\n>=\n>\n+"
      "\n-\n*\n/\n,\n.\n%\n;\n#\n||\n&&\n!");
  Lexer lex;
  TokenRules tokenRules = {{Token::WHITESPACE, "^(\\s+)"},
                           {Token::NUMBER, "^(\\d+)"},
                           {Token::IDENTIFIER, "^[a-zA-Z]+\\w*"},
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
                           {Token::INVERTED_COMMAS, "^(\")"},
                           {Token::UNDERSCORE, "^(_)"},
                           {Token::HASHTAG, "^(#)"},
                           {Token::OR, "^(\\|\\|)"},
                           {Token::AND, "^(&&)"},
                           {Token::NOT_EQUAL, "^(!=)"},
                           {Token::NOT, "^(!)"},
                           {Token::NEXT_LINE, "^(\n)"},
                           {Token::END, "^(\0)"}};

  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(str_stream);

  for (std::string line : lines) {
    std::vector<Token> new_tokens = lex.Lex(line, tokenRules);
    tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);

  REQUIRE(tokens.size() == 25);

  REQUIRE(tokens[0].GetValue() == "1");
  REQUIRE(tokens[1].GetValue() == "h1");

  std::vector<Token::Kind> k = {Token::NUMBER,
                                Token::IDENTIFIER,
                                Token::LEFT_ROUND_BRACKET,
                                Token::RIGHT_ROUND_BRACKET,
                                Token::LEFT_CURLY_BRACKET,
                                Token::RIGHT_CURLY_BRACKET,
                                Token::DOUBLE_EQUAL,
                                Token::EQUAL,
                                Token::LESS_THAN_OR_EQUAL,
                                Token::LESS_THAN,
                                Token::GREATER_THAN_OR_EQUAL,
                                Token::GREATER_THAN,
                                Token::PLUS,
                                Token::MINUS,
                                Token::ASTERISK,
                                Token::SLASH,
                                Token::COMMA,
                                Token::PERIOD,
                                Token::PERCENT,
                                Token::SEMICOLON,
                                Token::HASHTAG,
                                Token::OR,
                                Token::AND,
                                Token::NOT,
                                Token::END};

  for (int i = 0; i < (int)tokens.size(); i++) {
    REQUIRE(tokens[i].Is(k[i]));
  }
}

TEST_CASE("Extract if block code tokens", "[Lexer]") {
  Lexer lex;
  std::istringstream str_stream(
      "if (x==1) then {\n"
      "    z = x + 1; }");
  TokenRules tokenRules = {{Token::WHITESPACE, "^(\\s+)"},
                           {Token::NUMBER, "^(\\d+)"},
                           {Token::IDENTIFIER, "^[a-zA-Z]+\\w*"},
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
                           {Token::INVERTED_COMMAS, "^(\")"},
                           {Token::UNDERSCORE, "^(_)"},
                           {Token::HASHTAG, "^(#)"},
                           {Token::OR, "^(\\|\\|)"},
                           {Token::AND, "^(&&)"},
                           {Token::NOT_EQUAL, "^(!=)"},
                           {Token::NOT, "^(!)"},
                           {Token::NEXT_LINE, "^(\n)"},
                           {Token::END, "^(\0)"}};

  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(str_stream);

  for (std::string line : lines) {
    std::vector<Token> new_tokens = lex.Lex(line, tokenRules);
    tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);

  REQUIRE(tokens.size() == 16);

  std::vector<Token::Kind> k = {Token::IDENTIFIER,
                                Token::LEFT_ROUND_BRACKET,
                                Token::IDENTIFIER,
                                Token::DOUBLE_EQUAL,
                                Token::NUMBER,
                                Token::RIGHT_ROUND_BRACKET,
                                Token::IDENTIFIER,
                                Token::LEFT_CURLY_BRACKET,
                                Token::IDENTIFIER,
                                Token::EQUAL,
                                Token::IDENTIFIER,
                                Token::PLUS,
                                Token::NUMBER,
                                Token::SEMICOLON,
                                Token::RIGHT_CURLY_BRACKET,
                                Token::END};

  for (int i = 0; i < (int)tokens.size(); i++) {
    REQUIRE(tokens[i].Is(k[i]));
  }
}

TEST_CASE("Extract query pattern tokens", "[Lexer]") {
  Lexer lex;
  std::istringstream str_stream("Select a pattern a(_,_\"x + 1\"_");
  TokenRules tokenRules = {{Token::WHITESPACE, "^(\\s+)"},
                           {Token::NUMBER, "^(\\d+)"},
                           {Token::IDENTIFIER, "^[a-zA-Z]+\\w*"},
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
                           {Token::INVERTED_COMMAS, "^(\")"},
                           {Token::UNDERSCORE, "^(_)"},
                           {Token::HASHTAG, "^(#)"},
                           {Token::OR, "^(\\|\\|)"},
                           {Token::AND, "^(&&)"},
                           {Token::NOT_EQUAL, "^(!=)"},
                           {Token::NOT, "^(!)"},
                           {Token::NEXT_LINE, "^(\n)"},
                           {Token::END, "^(\0)"}};

  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(str_stream);

  for (std::string line : lines) {
    std::vector<Token> new_tokens = lex.Lex(line, tokenRules);
    tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);

  REQUIRE(tokens.size() == 15);

  std::vector<Token::Kind> k = {Token::IDENTIFIER,
                                Token::IDENTIFIER,
                                Token::IDENTIFIER,
                                Token::IDENTIFIER,
                                Token::LEFT_ROUND_BRACKET,
                                Token::UNDERSCORE,
                                Token::COMMA,
                                Token::UNDERSCORE,
                                Token::INVERTED_COMMAS,
                                Token::IDENTIFIER,
                                Token::PLUS,
                                Token::NUMBER,
                                Token::INVERTED_COMMAS,
                                Token::UNDERSCORE,
                                Token::END};

  for (int i = 0; i < (int)tokens.size(); i++) {
    REQUIRE(tokens[i].Is(k[i]));
  }
}
