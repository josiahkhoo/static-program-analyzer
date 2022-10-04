#include "catch.hpp"
#include "common/clause/calls_clause.h"
#include "common/clause/modifies_p_clause.h"
#include "common/clause/modifies_s_clause.h"
#include "common/clause/parent_clause.h"
#include "common/clause/parent_t_clause.h"
#include "common/clause/synonym_select.h"
#include "common/clause/uses_p_clause.h"
#include "common/clause/uses_s_clause.h"
#include "qps/query_parser.h"

TEST_CASE("Declaration flags", "[QPS Parser]") {
  SECTION("'Statement Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "stmt"), Token(Token::IDENTIFIER, "s"),
        Token(Token::SEMICOLON),          Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "s"),    Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::STATEMENT, "s");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Read Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "read"), Token(Token::IDENTIFIER, "r"),
        Token(Token::SEMICOLON),          Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "r"),    Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::READ, "r");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Print Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "print"), Token(Token::IDENTIFIER, "p"),
        Token(Token::SEMICOLON),           Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "p"),     Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::PRINT, "p");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Call Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "call"), Token(Token::IDENTIFIER, "c"),
        Token(Token::SEMICOLON),          Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "c"),    Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::CALL, "c");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'While Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "while"), Token(Token::IDENTIFIER, "w"),
        Token(Token::SEMICOLON),           Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "w"),     Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::WHILE, "w");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'If Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "if"), Token(Token::IDENTIFIER, "i"),
        Token(Token::SEMICOLON),        Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "i"),  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::IF, "i");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Assign Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::ASSIGN, "a");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Variable Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                  Token(Token::IDENTIFIER, "v"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "v"),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::VARIABLE, "v");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Constant Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "constant"),
                                  Token(Token::IDENTIFIER, "c"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "c"),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::CONSTANT, "c");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Procedure Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                  Token(Token::IDENTIFIER, "p"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "p"),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::PROCEDURE, "p");
    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn)});

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  }

  SECTION("'Assign Variable Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                  Token(Token::IDENTIFIER, "a"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "variable"),
                                  Token(Token::IDENTIFIER, "v"),
                                  Token(Token::SEMICOLON),
                                  Token(Token::IDENTIFIER, "Select"),
                                  Token(Token::IDENTIFIER, "v"),
                                  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn_a = Synonym(EntityType::ASSIGN, "a");
    Synonym syn_v = Synonym(EntityType::VARIABLE, "v");

    REQUIRE(res.GetSynonyms().size() == 2);
    REQUIRE(res.GetSynonyms()[0] == syn_a);
    REQUIRE(res.GetSynonyms()[1] == syn_v);

    std::shared_ptr<SynonymSelect> expected_select =
        std::make_shared<SynonymSelect>(
            std::vector{Select::SynonymWithMaybeAttribute(syn_v)});
    REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn_v);
  }
}

TEST_CASE("Every entity type", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "assign"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "while"),
                                Token(Token::IDENTIFIER, "while"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "if"),
                                Token(Token::IDENTIFIER, "if"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "print"),
                                Token(Token::IDENTIFIER, "print"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "call"),
                                Token(Token::IDENTIFIER, "call"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "constant"),
                                Token(Token::IDENTIFIER, "constant"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "variable");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  REQUIRE(res.GetSynonyms().size() == 8);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
}

TEST_CASE("'Assign Variable Statement Select' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn_assign = Synonym(EntityType::ASSIGN, "a");
  Synonym syn_var = Synonym(EntityType::VARIABLE, "v");
  Synonym syn_stmt = Synonym(EntityType::STATEMENT, "s");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn_assign)});

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn_assign);
  REQUIRE(res.GetSynonyms()[1] == syn_var);
  REQUIRE(res.GetSynonyms()[2] == syn_stmt);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn_assign);
}

TEST_CASE("'Assign Variable Variable Select' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "pattern"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "assign"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn_assign = Synonym(EntityType::ASSIGN, "pattern");
  Synonym syn_var1 = Synonym(EntityType::VARIABLE, "Select");
  Synonym syn_var2 = Synonym(EntityType::VARIABLE, "assign");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn_var1)});

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn_assign);
  REQUIRE(res.GetSynonyms()[1] == syn_var1);
  REQUIRE(res.GetSynonyms()[2] == syn_var2);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn_var1);
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
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());
}

TEST_CASE("'Assign Select FollowT' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsTClause f = FollowsTClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());
}

TEST_CASE("'Assign Select Parent' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref_1 = StatementReference();
  StatementReference statement_ref_2 = StatementReference(syn);
  ParentClause p = ParentClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == p.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == p.GetRightHandSide());
}

TEST_CASE("'Assign Select ParentT' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref_1 = StatementReference();
  StatementReference statement_ref_2 = StatementReference(syn);
  ParentTClause p = ParentTClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == p.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == p.GetRightHandSide());
}

TEST_CASE("Invalid 'Variable Select UsesS_' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("'Variable Select UsesSStmt' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref = StatementReference(1);
  EntityReference entity_ref = EntityReference(syn);
  UsesSClause u = UsesSClause(statement_ref, entity_ref);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == u.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == u.GetRightHandSide());
}

TEST_CASE("Invalid 'Variable Select UsesP_' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("'Variable Select UsesPIdent' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "identifier"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  EntityReference entity_ref_1 = EntityReference("identifier");
  EntityReference entity_ref_2 = EntityReference(syn);
  UsesPClause u = UsesPClause(entity_ref_1, entity_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == u.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == u.GetRightHandSide());
}

TEST_CASE("Invalid 'Variable Select ModifiesS_' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("'Variable Select ModifiesSStmt' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref = StatementReference(1);
  EntityReference entity_ref = EntityReference(syn);
  ModifiesSClause m = ModifiesSClause(statement_ref, entity_ref);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == m.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == m.GetRightHandSide());
}

TEST_CASE("Invalid 'Variable Select ModifiesP_' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("'Variable Select ModifiesPIdent' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "identifier"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  EntityReference entity_ref_1 = EntityReference("identifier");
  EntityReference entity_ref_2 = EntityReference(syn);
  ModifiesPClause m = ModifiesPClause(entity_ref_1, entity_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == m.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == m.GetRightHandSide());
}

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
  REQUIRE(res.GetSynonyms()[0] == syn);
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
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == c.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == c.GetRightHandSide());
}

TEST_CASE("`Assign PatternAssign Follow`", "[QPS Parser]") {
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
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_back_wildcard);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetRightHandSide() == f.GetRightHandSide());
}

TEST_CASE("`Assign Follow PatternAssign`", "[QPS Parser]") {
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
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());

  REQUIRE(res.GetQueryOperation().size() == 2);
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_back_wildcard);
}

TEST_CASE("UsesS Syn-Var", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  auto clause =
      std::dynamic_pointer_cast<UsesSClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetSynonym().GetIdentifier();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == "s");
  REQUIRE(clause_rhs == "v");
}

TEST_CASE("UsesS Stmt-Var", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  auto clause =
      std::dynamic_pointer_cast<UsesSClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetLineNumber();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == 1);
  REQUIRE(clause_rhs == "v");
}

TEST_CASE("UsesP Ident-Var", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  auto clause =
      std::dynamic_pointer_cast<UsesPClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetIdentifier();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == "s");
  REQUIRE(clause_rhs == "v");
}

TEST_CASE("ModifiesS Syn-Var", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  auto clause =
      std::dynamic_pointer_cast<ModifiesSClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetSynonym().GetIdentifier();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == "s");
  REQUIRE(clause_rhs == "v");
}

TEST_CASE("ModifiesS Stmt-Var", "[QPS Parser]") {
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
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  auto clause =
      std::dynamic_pointer_cast<ModifiesSClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetLineNumber();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == 1);
  REQUIRE(clause_rhs == "a");
}

TEST_CASE("ModifiesP Ident-Var", "[QPS Parser]") {
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

  auto clause =
      std::dynamic_pointer_cast<ModifiesPClause>(res.GetQueryOperation()[0]);
  auto clause_lhs = clause->GetLeftHandSide().GetIdentifier();
  auto clause_rhs = clause->GetRightHandSide().GetSynonym().GetIdentifier();
  REQUIRE(clause_lhs == "1");
  REQUIRE(clause_rhs == "a");
}

TEST_CASE("'End-less' query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {
      Token(Token::IDENTIFIER, "assign"), Token(Token::IDENTIFIER, "a"),
      Token(Token::SEMICOLON), Token(Token::IDENTIFIER, "Select"),
      Token(Token::IDENTIFIER, "a")};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
}

TEST_CASE("missing Select query", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("'Assign Select Follow Follow' query", "[QPS Parser]") {
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
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
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
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});

  StatementReference statement_ref = StatementReference(syn);
  StatementReference statement_ref_1 = StatementReference(syn1);
  StatementReference statement_ref_2 = StatementReference(syn2);
  FollowsClause f = FollowsClause(statement_ref, statement_ref_1);
  FollowsClause f1 = FollowsClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSynonyms()[1] == syn1);
  REQUIRE(res.GetSynonyms()[2] == syn2);
  REQUIRE(res.GetSelect()->GetSynonyms()[0].synonym == syn);
  REQUIRE(res.GetQueryOperation().size() == 2);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == f.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == f.GetRightHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetLeftHandSide() == f1.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[1])
              ->GetRightHandSide() == f1.GetRightHandSide());
}

TEST_CASE("`Assign PatternAssign PatternAssign`", "[QPS Parser]") {
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
                                Token(Token::IDENTIFIER, "pattern"),
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
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[0])
              ->GetExpression()
              .has_back_wildcard);

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> expected_select =
      std::make_shared<SynonymSelect>(
          std::vector{Select::SynonymWithMaybeAttribute(syn)});
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_front_wildcard);
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .to_match == "b");
  REQUIRE(std::dynamic_pointer_cast<PatternAssign>(res.GetQueryOperation()[1])
              ->GetExpression()
              .has_back_wildcard);
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

TEST_CASE("invalid Parent syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ParentT syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::ASTERISK),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid UsesS syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid UsesP syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::ASTERISK),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ModifiesS syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ModifiesP syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::ASTERISK),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
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

TEST_CASE("invalid Pattern syntax missing close bracket", "[QPS Parser]") {
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
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Pattern syntax missing open bracket", "[QPS Parser]") {
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
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::UNDERSCORE),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Pattern syntax open-ended operator", "[QPS Parser]") {
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
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::PLUS),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Pattern syntax open-ended long operator", "[QPS Parser]") {
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
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SLASH),
                                Token(Token::IDENTIFIER, "b"),
                                Token(Token::MINUS),
                                Token(Token::INVERTED_COMMAS),
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

TEST_CASE("invalid Select semi-colon syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, ";")};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Select semi-colon END syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, ";"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid clause that syntax", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Follows semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid FollowsT semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Follows"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Parent semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ParentT semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Parent"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid UsesSVar semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid UsesPStmt semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid UsesPVar semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Uses"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ModifiesPStmt semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "stmt"),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "s"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid ModifiesPVar semantics", "[QPS Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Modifies"),
                                Token(Token::ASTERISK),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "1"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("invalid Calls semantics", "[QPS Parser]") {
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

TEST_CASE("invalid CallsT semantics", "[QPS Parser]") {
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
