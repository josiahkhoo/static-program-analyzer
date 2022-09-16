#include "catch.hpp"
#include "common/clause/parent_clause.h"
#include "common/clause/parent_t_clause.h"
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
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
  }

  SECTION("'Read Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "read"), Token(Token::IDENTIFIER, "r"),
        Token(Token::SEMICOLON),          Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "r"),    Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::READ, "r");
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
  }

  SECTION("'Print Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "print"), Token(Token::IDENTIFIER, "p"),
        Token(Token::SEMICOLON),           Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "p"),     Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::PRINT, "p");
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
  }

  SECTION("'Call Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "call"), Token(Token::IDENTIFIER, "c"),
        Token(Token::SEMICOLON),          Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "c"),    Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::CALL, "c");
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
  }

  SECTION("'While Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "while"), Token(Token::IDENTIFIER, "w"),
        Token(Token::SEMICOLON),           Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "w"),     Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::WHILE, "w");
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
  }

  SECTION("'If Select' query") {
    QueryParser qp = QueryParser();
    std::vector<Token> tokens_ = {
        Token(Token::IDENTIFIER, "if"), Token(Token::IDENTIFIER, "i"),
        Token(Token::SEMICOLON),        Token(Token::IDENTIFIER, "Select"),
        Token(Token::IDENTIFIER, "i"),  Token(Token::END)};
    QueryString res = qp.Parse(tokens_);

    Synonym syn = Synonym(EntityType::IF, "i");
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
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
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
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
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
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
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
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
    Select expected_select = Select(syn);

    REQUIRE(res.GetSynonyms().size() == 1);
    REQUIRE(res.GetSynonyms()[0] == syn);
    REQUIRE(res.GetSelect().GetSynonym() == syn);
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

    Select expected_select = Select(syn_v);
    REQUIRE(res.GetSelect().GetSynonym() == syn_v);
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
  Select expected_select = Select(syn);

  REQUIRE(res.GetSynonyms().size() == 8);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
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
  Select expected_select = Select(syn_assign);

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn_assign);
  REQUIRE(res.GetSynonyms()[1] == syn_var);
  REQUIRE(res.GetSynonyms()[2] == syn_stmt);
  REQUIRE(res.GetSelect().GetSynonym() == syn_assign);
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
  Select expected_select = Select(syn_var1);

  REQUIRE(res.GetSynonyms().size() == 3);
  REQUIRE(res.GetSynonyms()[0] == syn_assign);
  REQUIRE(res.GetSynonyms()[1] == syn_var1);
  REQUIRE(res.GetSynonyms()[2] == syn_var2);
  REQUIRE(res.GetSelect().GetSynonym() == syn_var1);
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
  Select expected_select = Select(syn);

  StatementReference statement_ref_1 = StatementReference();
  StatementReference statement_ref_2 = StatementReference(syn);
  ParentClause p = ParentClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
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
  Select expected_select = Select(syn);

  StatementReference statement_ref_1 = StatementReference();
  StatementReference statement_ref_2 = StatementReference(syn);
  ParentTClause p = ParentTClause(statement_ref_1, statement_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == p.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == p.GetRightHandSide());
}

TEST_CASE("'Variable Select UsesS' query", "[QPS Parser]") {
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
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  Select expected_select = Select(syn);

  StatementReference statement_ref = StatementReference();
  EntityReference entity_ref = EntityReference(syn);
  UsesSClause u = UsesSClause(statement_ref, entity_ref);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == u.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == u.GetRightHandSide());
}

TEST_CASE("'Variable Select UsesP' query", "[QPS Parser]") {
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
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::UNDERSCORE),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  Synonym syn = Synonym(EntityType::VARIABLE, "v");
  Select expected_select = Select(syn);

  EntityReference entity_ref_1 = EntityReference();
  EntityReference entity_ref_2 = EntityReference(syn);
  UsesPClause u = UsesPClause(entity_ref_1, entity_ref_2);

  REQUIRE(res.GetSynonyms().size() == 1);
  REQUIRE(res.GetSynonyms()[0] == syn);
  REQUIRE(res.GetSelect().GetSynonym() == syn);
  REQUIRE(res.GetQueryOperation().size() == 1);
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetLeftHandSide() == u.GetLeftHandSide());
  REQUIRE(std::dynamic_pointer_cast<Clause>(res.GetQueryOperation()[0])
              ->GetRightHandSide() == u.GetRightHandSide());
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

TEST_CASE("Pattern Wildcards", "[QPS Parser]") {
  SECTION("Only wildcard") {
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
  SECTION("Front only wildcard") {
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
}

TEST_CASE("Pattern patterns (string)", "[QPS Parser]") {
  SECTION("Short string") {
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