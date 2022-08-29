#include "token.h"

#include <cassert>
#include <unordered_map>

Token::Token(Token::Kind kind) : kind_(kind) { assert(!CanHoldValue(kind)); }

Token::Token(Token::Kind kind, std::string value) : kind_(kind) {
  assert(CanHoldValue(kind));
  value_.emplace(value);
}

bool Token::Is(Token::Kind kind) { return kind_ == kind; }

bool Token::IsNot(Token::Kind kind) { return !Is(kind); }

bool Token::CanHoldValue(Kind kind) {
  return kind == NUMBER || kind == IDENTIFIER;
}

std::string Token::GetValue() const {
  assert(CanHoldValue(kind_));
  return value_.value();
}

std::string Token::PrettyPrintKind() const {
  std::unordered_map<Token::Kind, std::string> mapper = {
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
  return mapper[kind_];
}