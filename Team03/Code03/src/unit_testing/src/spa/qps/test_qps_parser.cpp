#include <iostream>

#include "catch.hpp"
#include "qps/query_parser.h"

TEST_CASE("'Assign Select' query", "[QPS Parser]") {
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

TEST_CASE("'Assign Select Follow' query", "[QPS Parser]") {
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
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());
}

TEST_CASE("'Assign Select Pattern' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
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

TEST_CASE("Pattern front wildcard query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
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

TEST_CASE("Pattern front & back wildcard query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
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

TEST_CASE("`Assign Pattern Follow`", "[QPS Parser]") {
  QueryParser qp = QueryParser();
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

  REQUIRE(res.GetQueryOperation().size() == 2);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_back_wildcard);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select expected_select = Select(syn);
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetRightHandSide() == f.GetRightHandSide());
}

TEST_CASE("`Assign Follow Pattern`", "[QPS Parser]") {
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

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select expected_select = Select(syn);
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());

  REQUIRE(res.GetQueryOperation().size() == 2);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[1])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<Pattern>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_back_wildcard);
}

TEST_CASE("'End-less' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {
      Token(Token::IDENTIFIER, "assign"), Token(Token::IDENTIFIER, "a"),
      Token(Token::SEMICOLON), Token(Token::IDENTIFIER, "Select"),
      Token(Token::IDENTIFIER, "a")};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select expected_select = Select(syn);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
}

TEST_CASE("missing Select query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Follows syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Pattern syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::COMMA),
                                Token(Token::UNDERSCORE),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Such That syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}