#define DEBUG 0

#include "lexer.h"

#include <iostream>
#include <istream>
#include <map>
#include <regex>

#include "token.h"

std::string prettyPrintType(Token::Kind t) {
  std::map<Token::Kind, std::string> m = {
      {Token::WHITESPACE, "WHTESPACE"},
      {Token::NUMBER, "NUMBER"},
      {Token::IDENTIFIER, "IDENTIFIER"},
      {Token::LEFT_ROUND_BRACKET, "LEFT_ROUND_BRACKET"},
      {Token::RIGHT_ROUND_BRACKET, "RIGHT_ROUND_BRACKET"},
      {Token::LEFT_CURLY_BRACKET, "LEFT_CURLY_BRACKET"},
      {Token::RIGHT_CURLY_BRACKET, "RIGHT_CURLY_BRACKET"},
      {Token::DOUBLE_EQUAL, "DOUBLE_EQUAL"},
      {Token::EQUAL, "EQUAL"},
      {Token::LESS_THAN, "LESS_THAN"},
      {Token::LESS_THAN_OR_EQUAL, "LESS_THAN_OR_EQUAL"},
      {Token::GREATER_THAN, "GREATER_THAN"},
      {Token::GREATER_THAN_OR_EQUAL, "GREATER_THAN_OR_EQUAL"},
      {Token::PLUS, "PLUS"},
      {Token::MINUS, "MINUS"},
      {Token::ASTERISK, "ASTERISK"},
      {Token::SLASH, "SLASH"},
      {Token::COMMA, "COMMA"},
      {Token::PERCENT, "PERCENT"},
      {Token::SEMICOLON, "SEMICOLON"},
      {Token::OR, "OR"},
      {Token::AND, "AND"},
      {Token::NOT, "NOT"},
      {Token::NEXT_LINE, "NEXT_LINE"},
      {Token::END, "END"}};
  return m[t];
}

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
    {Token::NOT, "^(!)"},
    {Token::NEXT_LINE, "^(\n)"},
    {Token::END, "^(\0)"}
};

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
std::vector<Token> Lexer::lex(std::istream& stream) {
  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(stream);

  for (int line_no = 1; line_no <= lines.size(); line_no++) {
    std::string line = lines[line_no - 1];
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
            std::cout << prettyPrintType(pair.first) << ", "
                      << matched_regex.str() << "\n";

          line = line.substr(static_cast<int>(matched_regex.str().size()));
          break;
        }
      }
    }
  }
  return tokens;
}