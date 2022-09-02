#define DEBUG 0

#include "lexer.h"

#include <iostream>
#include <istream>
#include <regex>

#include "token.h"

std::vector<std::pair<Token::Kind, std::string>> rules = {
    {Token::WHITESPACE, "^(\\s+)"},
    {Token::NUMBER, "^(\\d+)"},
    {Token::IDENTIFIER, "^([A-Za-z]\\w*([0-9])?)\\b"},
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
    {Token::PERCENT, "^(%)"},
    {Token::SEMICOLON, "^(;)"},
    {Token::OR, "^(\\|\\|)"},
    {Token::AND, "^(&&)"},
    {Token::NOT_EQUAL, "^(!=)"},
    {Token::NOT, "^(!)"},
    {Token::NEXT_LINE, "^(\n)"},
    {Token::END, "^(\0)"}};

// Splits given stream of text into a list of lines
std::vector<std::string> splitLines(std::istream& stream) {
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(stream, line)) {
    lines.push_back(line);
  }

  return lines;
}

// Generates given stream of lex into tokens
std::vector<Token> Lexer::Lex(std::istream& stream) const {
  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(stream);

  for (std::string line : lines) {
    while (!line.empty()) {
      for (auto const& pair : rules) {
        std::smatch matched_regex;
        if (std::regex_search(line, matched_regex, std::regex(pair.second))) {
          if (pair.first == Token::IDENTIFIER || pair.first == Token::NUMBER) {
            Token found_token(pair.first, matched_regex.str());
            tokens.push_back(found_token);
          } else if (pair.first != Token::WHITESPACE) {
            Token found_token(pair.first);
            tokens.push_back(found_token);
          }
          // else skip whitespaces

          if (DEBUG)
            std::cout << tokens.back().PrettyPrintKind() << ", "
                      << matched_regex.str() << "\n";

          line = line.substr(static_cast<int>(matched_regex.str().size()));
          break;
        }
      }
    }
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);
  return tokens;
}