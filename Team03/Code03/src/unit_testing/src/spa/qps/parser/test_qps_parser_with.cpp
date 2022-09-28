#include "catch.hpp"
#include "common/clause/with.h"
#include "qps/query_parser.h"

TEST_CASE("Variable WITH varName Single-Syn", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
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
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  std::shared_ptr<With> withCl =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[0]);
  REQUIRE(withCl->GetSynonym().IsEntityType(VARIABLE));
  REQUIRE(withCl->GetType() == QueryOperation::SINGLE_SYNONYM);
}

TEST_CASE("Procedure WITH procName procName Double-Syn",
          "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "p1"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "procName"),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "p1"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "procName"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  std::shared_ptr<With> withCl =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[0]);
  REQUIRE(withCl->GetType() == QueryOperation::DOUBLE_SYNONYM);
  REQUIRE(withCl->GetSynonymPair().first.IsEntityType(PROCEDURE));
  REQUIRE(withCl->GetSynonymPair().second.IsEntityType(PROCEDURE));
}

TEST_CASE("Procedure WITH procName varName Double-Syn",
          "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "procName"),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  std::shared_ptr<With> withCl =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[0]);
  REQUIRE(withCl->GetType() == QueryOperation::DOUBLE_SYNONYM);
  REQUIRE(withCl->GetSynonymPair().first.IsEntityType(PROCEDURE));
  REQUIRE(withCl->GetSynonymPair().second.IsEntityType(VARIABLE));
}

TEST_CASE("WITH identifier identifier No-synonym", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::EQUAL),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE(res.GetQueryOperation().size() == 1);
  std::shared_ptr<With> withCl =
      std::dynamic_pointer_cast<With>(res.GetQueryOperation()[0]);
  REQUIRE(withCl->GetType() == QueryOperation::NO_SYNONYM);
}

TEST_CASE("Invalid WITH identifier syn", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid WITH number identifier", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::NUMBER, "2"),
                                Token(Token::EQUAL),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::IDENTIFIER, "p"),
                                Token(Token::INVERTED_COMMAS),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid WITH NAME VALUE", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::EQUAL),
                                Token(Token::NUMBER, "1"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid WITH VALUE NAME", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "procedure"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::NUMBER, "1"),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "procName"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid WITH VALUE NAME attr", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "stmt#"),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}

TEST_CASE("Invalid attribute procName variable", "[QPS Pattern Parser]") {
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "variable"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::IDENTIFIER, "with"),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "procName"),
                                Token(Token::EQUAL),
                                Token(Token::IDENTIFIER, "v"),
                                Token(Token::PERIOD),
                                Token(Token::IDENTIFIER, "varName"),
                                Token(Token::END)};
  REQUIRE_THROWS(qp.Parse(tokens_));
}