#include "lexer.h"

#include <istream>
#include <regex>

#include "common/exceptions/syntax_exception.h"

std::vector<Token> Lexer::Lex(
    std::string &line,
    std::vector<std::pair<Token::Kind, std::string>> &token_rules) const {
  std::vector<Token> tokens;
  while (!line.empty()) {
    ProcessLineHead(line, tokens, token_rules);
  }
  return tokens;
}

void Lexer::ProcessLineHead(
    std::string &line, std::vector<Token> &tokens,
    std::vector<std::pair<Token::Kind, std::string>> &token_rules) {
  for (auto const &pair : token_rules) {
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
