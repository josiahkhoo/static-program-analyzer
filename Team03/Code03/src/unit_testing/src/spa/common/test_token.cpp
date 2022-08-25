//
// Created by Josiah Khoo on 25/8/22.
//

#include "catch.hpp"
#include "common/token.h"

TEST_CASE("Construct not-value token", "[token]") {
  Token t = Token(Token::AND);
  REQUIRE(t.Is(Token::AND));
  REQUIRE_FALSE(t.Is(Token::OR));
}

TEST_CASE("Construct value token", "[token]") {
  std::string val = "123";
  Token t = Token(Token::NUMBER, val);
  REQUIRE(t.Is(Token::NUMBER));
  REQUIRE(t.GetValue() == val);
  REQUIRE_FALSE(t.Is(Token::IDENTIFIER));
}