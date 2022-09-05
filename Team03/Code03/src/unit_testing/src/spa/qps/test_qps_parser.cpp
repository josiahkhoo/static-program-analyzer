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

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select expected_select = Select(syn);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
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

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select expected_select = Select(syn);

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
  REQUIRE(res.GetClause().size() == 1);
  REQUIRE(res.GetClause()[0] == f);
}
