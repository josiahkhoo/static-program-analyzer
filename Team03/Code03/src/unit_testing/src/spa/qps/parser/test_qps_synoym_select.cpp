#include "catch.hpp"
#include "qps/query_parser.h"

TEST_CASE("Tuple: Single synonym select", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::NUMBER, "1"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetSelect()->GetSynonyms().size() == 1);

  Select::SynonymWithMaybeAttribute expectedSynAttr = {Synonym(VARIABLE, "a")};
  Select::SynonymWithMaybeAttribute resultSynAttr =
      res.GetSelect()->GetSynonyms()[0];

  REQUIRE(resultSynAttr.synonym == expectedSynAttr.synonym);
  REQUIRE(resultSynAttr.maybe_attribute == expectedSynAttr.maybe_attribute);
}

TEST_CASE("Tuple: Double synonym select", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::LESS_THAN),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::GREATER_THAN),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::NUMBER, "1"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetSelect()->GetSynonyms().size() == 2);

  Select::SynonymWithMaybeAttribute expectedSynAttr = {Synonym(VARIABLE, "a1")};
  Select::SynonymWithMaybeAttribute resultSynAttr =
      res.GetSelect()->GetSynonyms()[1];

  REQUIRE(resultSynAttr.synonym == expectedSynAttr.synonym);
  REQUIRE(resultSynAttr.maybe_attribute == expectedSynAttr.maybe_attribute);
}

TEST_CASE("Tuple: Triple synonym select", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::LESS_THAN),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::GREATER_THAN),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::NUMBER, "1"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetSelect()->GetSynonyms().size() == 3);

  Select::SynonymWithMaybeAttribute expectedSynAttr = {Synonym(ASSIGN, "v")};
  Select::SynonymWithMaybeAttribute resultSynAttr =
      res.GetSelect()->GetSynonyms()[2];

  REQUIRE(resultSynAttr.synonym == expectedSynAttr.synonym);
  REQUIRE(resultSynAttr.maybe_attribute == expectedSynAttr.maybe_attribute);
}