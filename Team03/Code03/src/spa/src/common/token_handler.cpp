#include "token_handler.h"

#include <utility>

#include "common/exceptions/syntax_exception.h"

TokenHandler::TokenHandler() = default;

TokenHandler::TokenHandler(std::vector<Token> tokens)
    : tokens_(std::move(tokens)) {}

Token TokenHandler::Peek() {
  if (token_pos_ >= int(tokens_.size())) {
    throw SyntaxException("No more tokens");
  }
  return tokens_[token_pos_];
}

std::string TokenHandler::PeekValue() {
  if (token_pos_ >= int(tokens_.size())) {
    throw SyntaxException("No more tokens");
  }
  return tokens_[token_pos_].GetValue();
}

bool TokenHandler::MatchKind(Token::Kind kind) { return Peek().Is(kind); }

bool TokenHandler::MatchString(const std::string& s) {
  Token next = Peek();
  if (next.IsNot(Token::IDENTIFIER)) {
    return false;
  }
  return (next.GetValue() == s);
}

bool TokenHandler::CheckEnd() { return token_pos_ == int(tokens_.size()); }

void TokenHandler::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw SyntaxException("Expected different token");
  }
}

void TokenHandler::Expect(const std::string& s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw SyntaxException("Expected different string");
  }
}

void TokenHandler::Forward() { token_pos_++; }

void TokenHandler::Back() { token_pos_--; }

bool TokenHandler::IsNotEnd() { return (token_pos_ < int(tokens_.size()) - 1); }

bool TokenHandler::IsMathOperator() {
  Token next = Peek();
  return next.Is(Token::PLUS) || next.Is(Token::MINUS) ||
         next.Is(Token::ASTERISK) || next.Is(Token::SLASH) ||
         next.Is(Token::PERCENT);
}

bool TokenHandler::IsVarOrConst() {
  Token next = Peek();
  return next.Is(Token::IDENTIFIER) || next.Is(Token::NUMBER);
}

bool TokenHandler::CheckAhead(Token::Kind kind) {
  if (MatchKind(kind)) {
    return true;
  }
  Forward();
  if (MatchKind(kind)) {
    return true;
  }
  Back();
  return false;
}


int TokenHandler::GetTokenPos() { return token_pos_; }

void TokenHandler::SetTokenPos(int token_pos) { token_pos_ = token_pos; }