#include "token.h"
#include <cassert>

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
