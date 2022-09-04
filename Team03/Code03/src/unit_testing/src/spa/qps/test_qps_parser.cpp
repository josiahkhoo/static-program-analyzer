#include "catch.hpp"
#include "qps/query_parser.h"

TEST_CASE("Test 'Assign Select' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  EntityReference e;
  e.SetIdentifier("a");
  Select expected_select = Select(e);

  REQUIRE(res.GetEntities().front().GetIdentifier() == e.GetIdentifier());
  REQUIRE(res.GetSelect().GetEntity().GetIdentifier() ==
          expected_select.GetEntity().GetIdentifier());
}

TEST_CASE("Test 'Assign Select Follow' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  EntityReference e;
  e.SetIdentifier("a");
  Select expected_select = Select(e);

  REQUIRE(res.GetEntities().front().GetIdentifier() == e.GetIdentifier());
  REQUIRE(res.GetSelect().GetEntity().GetIdentifier() ==
          expected_select.GetEntity().GetIdentifier());
  REQUIRE(res.GetClause().size() == 1);
}
