#include "catch.hpp"
#include "common/clause/modifies_p_clause.h"
#include "common/clause/modifies_s_clause.h"
#include "common/clause/synonym_select.h"
#include "qps/query_parser.h"

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

TEST_CASE("Invalid ModifiesS syntax", "[QPS Parser]") {
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

TEST_CASE("Invalid ModifiesP syntax", "[QPS Parser]") {
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

TEST_CASE("Invalid ModifiesPStmt semantics", "[QPS Parser]") {
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

TEST_CASE("Invalid ModifiesPVar semantics", "[QPS Parser]") {
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