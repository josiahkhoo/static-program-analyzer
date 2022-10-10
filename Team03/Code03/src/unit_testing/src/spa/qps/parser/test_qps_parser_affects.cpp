#include "catch.hpp"
#include "common/clause/affects_clause.h"
#include "common/clause/affects_t_clause.h"
#include "common/clause/synonym_select.h"
#include "qps/query_parser.h"

TEST_CASE("'Assign Select Affects' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a1");
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(syn1);
  AffectsClause a = AffectsClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 2);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSynonyms()[1] == syn1);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == a.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == a.GetRightHandSide());
}

TEST_CASE("'Assign Select AffectsT' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a1");
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(syn1);
  AffectsTClause a = AffectsTClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 2);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSynonyms()[1] == syn1);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == a.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == a.GetRightHandSide());
}

TEST_CASE("Invalid Affects stmt synonym type", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "s1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "s1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid AffectsT stmt synonym type", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "s1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "s1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}
