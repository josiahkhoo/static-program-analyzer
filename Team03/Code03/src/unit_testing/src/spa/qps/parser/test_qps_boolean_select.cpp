#include "catch.hpp"
#include "qps/query_parser.h"

TEST_CASE("Boolean select", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "BOOLEAN"),
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

  REQUIRE(res.GetSelect()->GetSynonyms().empty());
}

TEST_CASE("Boolean select: No declarations", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "BOOLEAN"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::NUMBER, "2"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetSelect()->GetSynonyms().empty());
}