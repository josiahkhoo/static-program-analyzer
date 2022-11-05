#include "../../../helper.hpp"
#include "catch.hpp"
#include "common/clause/calls_clause.h"
#include "common/clause/synonym_select.h"
#include "qps/query_parser.h"

TEST_CASE("'Procedure Select Calls' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::PROCEDURE, "p");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  EntityReference entity_ref_1 = EntityReference(syn);
  EntityReference entity_ref_2 =
      EntityReference(Synonym(EntityType::PROCEDURE, "q"));
  CallsClause c = CallsClause(entity_ref_1, entity_ref_2);

  REQUIRE(res.GetSynonyms().size() == 2);
  REQUIRE(contains(res.GetSynonyms(), syn));
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == c.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == c.GetRightHandSide());
}

TEST_CASE("'Procedure Select CallsT' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::PROCEDURE, "p");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  EntityReference entity_ref_1 = EntityReference(syn);
  EntityReference entity_ref_2 =
      EntityReference(Synonym(EntityType::PROCEDURE, "q"));
  CallsClause c = CallsClause(entity_ref_1, entity_ref_2);

  REQUIRE(res.GetSynonyms().size() == 2);
  REQUIRE(contains(res.GetSynonyms(), syn));
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == c.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == c.GetRightHandSide());
}

TEST_CASE("invalid Calls syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid CallsT syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::ASTERISK),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid Calls syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid CallsT syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::ASTERISK),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid Calls semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid CallsT semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Calls"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "q"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}
