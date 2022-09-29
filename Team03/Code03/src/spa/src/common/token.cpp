#include "token.h"

#include <cassert>
#include <unordered_map>

std::unordered_map<Token::Kind, std::string> token_representation = {
    {Token::LEFT_ROUND_BRACKET, "("},
    {Token::RIGHT_ROUND_BRACKET, ")"},
    {Token::LEFT_CURLY_BRACKET, "{"},
    {Token::RIGHT_CURLY_BRACKET, "}"},
    {Token::DOUBLE_EQUAL, "=="},
    {Token::EQUAL, "="},
    {Token::NOT_EQUAL, "!="},
    {Token::LESS_THAN, "<"},
    {Token::LESS_THAN_OR_EQUAL, "<="},
    {Token::GREATER_THAN, ">"},
    {Token::GREATER_THAN_OR_EQUAL, ">="},
    {Token::PLUS, "+"},
    {Token::MINUS, "-"},
    {Token::ASTERISK, "*"},
    {Token::SLASH, "/"},
    {Token::COMMA, ","},
    {Token::PERIOD, "."},
    {Token::PERCENT, "%"},
    {Token::SEMICOLON, ";"},
    {Token::OR, "||"},
    {Token::AND, "&&"},
    {Token::NOT, "!"},
};

Token::Token(Token::Kind kind) : kind_(kind) { assert(!CanHoldValue(kind)); }

Token::Token(Token::Kind kind, const std::string& value) : kind_(kind) {
  assert(CanHoldValue(kind));
  value_.emplace(value);
}

bool Token::Is(Token::Kind kind) { return kind_ == kind; }

bool Token::IsNot(Token::Kind kind) { return !Is(kind); }

bool Token::CanHoldValue(Kind kind) {
  return kind == NUMBER || kind == IDENTIFIER;
}

std::string Token::GetValue() const {
  if (CanHoldValue(kind_)) {
    return value_.value();
  }
  return GetTypeValue(kind_);
}

std::string Token::GetTypeValue(Token::Kind kind) {
  if (token_representation.count(kind)) {
    return token_representation[kind];
  }
  return "";
}
