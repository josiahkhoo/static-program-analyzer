#include "catch.hpp"
#include "common/clause/pattern_assign.h"
#include "common/clause/synonym_select.h"
#include "common/clause/with.h"
#include "qps/query_parser.h"

TEST_CASE("Assign Follow And", "[QPS And Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a2"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "and"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a2"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a1");
  Synonym syn2 = Synonym(EntityType::ASSIGN, "a2");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(std::vector{syn});

  StatementReference statement_ref = StatementReference(syn);
  StatementReference statement_ref_1 = StatementReference(syn1);
  StatementReference statement_ref_2 = StatementReference(syn2);
  FollowsClause f = FollowsClause(statement_ref, statement_ref_1);
  FollowsClause f1 = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSynonyms()[1] == syn1);
  REQUIRE(res.GetSynonyms()[2] == syn2);
  REQUIRE(res.GetSelect()->GetSynonyms()[0] == syn);
  REQUIRE(res.GetQueryOperation().size() == 2);
  std::shared_ptr<Clause> cl =
      std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0]);
  REQUIRE(cl->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(cl->GetRightHandSide() == f.GetRightHandSide());
  std::shared_ptr<Clause> cl1 =
      std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1]);
  REQUIRE(cl1->GetLeftHandSide() == f1.GetLeftHandSide());
  REQUIRE(cl1->GetRightHandSide() == f1.GetRightHandSide());
}

TEST_CASE("Assign PatternAssign And", "[QPS And Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
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
                                Token(Token::IDENTIFIER, "and"),
                                Token(Token::IDENTIFIER, "a1"),
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

  REQUIRE(res.GetQueryOperation().size() == 2);
  std::shared_ptr<PatternAssign> ptrnAssign =
      std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0]);
  REQUIRE(ptrnAssign->GetExpression().has_front_wildcard);
  REQUIRE(ptrnAssign->GetExpression().to_match == "b");
  REQUIRE(ptrnAssign->GetExpression().has_back_wildcard);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(std::vector{syn});
  std::shared_ptr<PatternAssign> ptrnAssign1 =
      std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1]);
  REQUIRE(ptrnAssign1->GetExpression().has_front_wildcard);
  REQUIRE(ptrnAssign1->GetExpression().to_match == "b");
  REQUIRE(ptrnAssign1->GetExpression().has_back_wildcard);
}

TEST_CASE("Variable WITH And", "[QPS And Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::EQUAL),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "x"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "and"),
                                Token(Token::IDENTIFIER, "v1"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::EQUAL),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "x1"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 2);
  std::shared_ptr<With> withCl =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[0]);
  REQUIRE(withCl->GetSynonym().IsEntityType(VARIABLE));
  REQUIRE(withCl->GetType() == QueryOperation::SINGLE_SYNONYM);
  std::shared_ptr<With> withCl1 =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[1]);
  REQUIRE(withCl1->GetSynonym().IsEntityType(VARIABLE));
  REQUIRE(withCl1->GetType() == QueryOperation::SINGLE_SYNONYM);
}

TEST_CASE("invalid And syntax", "[QPS And Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a2"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "and"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a2"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}
