#include "catch.hpp"
#include "qps/query_parser.h"

QueryParser qp = QueryParser();

/// =============== ASSIGN TEST CASES =============== ///

TEST_CASE("Pattern ASSIGN Single-Syn", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonym()
              .IsEntityType(ASSIGN));
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetEntity().IsWildCard());
  REQUIRE_FALSE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .to_match == "b");
  REQUIRE_FALSE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                    ->GetExpression()
                    .has_back_wildcard);
}

TEST_CASE("Pattern ASSIGN Double-Syn", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::COMMA),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonymPair().first.IsEntityType(ASSIGN));
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonymPair().second.IsEntityType(VARIABLE));
  REQUIRE_FALSE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                    ->GetExpression()
                    .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .to_match == "b");
  REQUIRE_FALSE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                    ->GetExpression()
                    .has_back_wildcard);
}

TEST_CASE("Pattern Wildcards", "[QPS Pattern Parser]") {
  SECTION("Only wildcard") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(res.GetQueryOperation().size() == 1);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .has_front_wildcard);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match.empty());
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .has_back_wildcard);
  }
  SECTION("Front & back wildcard") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(res.GetQueryOperation().size() == 1);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .has_front_wildcard);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "b");
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .has_back_wildcard);
  }
  SECTION("Front only wildcard") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(res.GetQueryOperation().size() == 1);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .has_front_wildcard);
    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "b");
    REQUIRE_FALSE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                      ->GetExpression()
                      .has_back_wildcard);
  }
}

TEST_CASE("Pattern patterns (string)", "[QPS Pattern Parser]") {
  SECTION("Short string") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::PLUS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "a+b");
  }
  SECTION("Long string") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::PLUS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::MINUS),
                                  Token(Token::IDENTIFIER, "c"),
                                  Token(Token::PERCENT),
                                  Token(Token::IDENTIFIER, "d"),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "a+b-c%d");
  }
  SECTION("Bracket string") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::PLUS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "(a+b)");
  }
  SECTION("Double Bracket string") {
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::IDENTIFIER, "pattern"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::UNDERSCORE),
                                  Token(Token::COMMA),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::LEFT_ROUND_BRACKET),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::PLUS),
                                  Token(Token::IDENTIFIER, "b"),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::INVERTED_COMMAS),
                                  Token(Token::RIGHT_ROUND_BRACKET),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
                ->GetExpression()
                .to_match == "((a)+b)");
  }
}

TEST_CASE("invalid Pattern ASSIGN semantics", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "constant"),
                                Token(Token::IDENTIFIER, "c"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "c"),
                                Token(Token::COMMA),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

/// =============== IF TEST CASES =============== ///

TEST_CASE("Pattern IF Single-Syn", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "if"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonym()
              .IsEntityType(IF));
}

TEST_CASE("Pattern IF Double-Syn", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "if"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonymPair().first.IsEntityType(IF));
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonymPair().second.IsEntityType(VARIABLE));
}

TEST_CASE("invalid Pattern IF: _,not wildcard", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "if"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "x"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Pattern IF: not wildcard,_", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "if"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "i"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

/// =============== WHILE TEST CASES =============== ///

TEST_CASE("Pattern WHILE Single-Syn", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "while"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonym()
              .IsEntityType(WHILE));
}

TEST_CASE("Pattern WHILE Single-Syn Ident", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "while"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "x"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetSynonym()
              .IsEntityType(WHILE));
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetEntity().GetIdentifier() == "x");
}

TEST_CASE("invalid Pattern WHILE: not wildcard", "[QPS Pattern Parser]") {
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "while"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "w"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::NUMBER, "2"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}