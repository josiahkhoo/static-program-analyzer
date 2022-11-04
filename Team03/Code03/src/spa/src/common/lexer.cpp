#include "lexer.h"

#include <istream>
#include <regex>

#include "common/exceptions/syntax_exception.h"

std::vector<std::pair<Token::Kind, std::string>> tokenRules = {
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

// Splits given stream of text into a list of lines
std::vector<std::string> splitLines(std::istream &stream) {
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(stream, line)) {
    lines.push_back(line);
  }

  return lines;
}

// Generates given stream of lex into tokens
std::vector<Token> Lexer::Lex(std::istream &stream) const {
  std::vector<Token> tokens;
  std::vector<std::string> lines = splitLines(stream);

  for (std::string line : lines) {
    std::vector<Token> new_tokens = LexLine(line);
    tokens.insert(tokens.end(), new_tokens.begin(), new_tokens.end());
  }
  Token end_token = Token(Token::END);
  tokens.push_back(end_token);
  return tokens;
}

std::vector<Token> Lexer::LexLine(std::string &line) const {
  std::vector<Token> tokens;
  while (!line.empty()) {
    ProcessLineHead(line, tokens);
  }
  return tokens;
}

void Lexer::ProcessLineHead(std::string &line, std::vector<Token> &tokens) {
  for (auto const &pair : tokenRules) {
    std::smatch matched_regex;
    try {
      if (std::regex_search(line, matched_regex, std::regex(pair.second))) {
        FindTokens(tokens, pair, matched_regex);
        line = line.substr(static_cast<int>(matched_regex.str().size()));
        break;
      }
    } catch (...) {
      throw SyntaxException("Invalid character");
    }
  }
}

void Lexer::FindTokens(std::vector<Token> &tokens,
                       const std::pair<Token::Kind, std::string> &pair,
                       const std::smatch &matched_regex) {
  if (pair.first == Token::WHITESPACE) {  // Skip whitespaces
    return;
  }
  if (pair.first == Token::IDENTIFIER || pair.first == Token::NUMBER) {
    Token found_token(pair.first, matched_regex.str());
    tokens.push_back(found_token);
    return;
  }
  Token found_token(pair.first);
  tokens.push_back(found_token);
}
