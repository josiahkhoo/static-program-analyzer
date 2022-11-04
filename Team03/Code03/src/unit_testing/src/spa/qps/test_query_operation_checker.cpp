#include "catch.hpp"
#include "common/clause/synonym_select.h"
#include "qps/query_operation_checker.h"
#include "qps/query_parser.h"

class QueryOpCheckPkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls() const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryNextT(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int, EntityType) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffects() override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllAffectsBy() override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAffects(int) override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsBy(int) override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsT(int) override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAffectsTBy(int) override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string, Expression) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllWhilePattern()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWhilePattern(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllIfPattern()
      const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryIfPattern(
      std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int) const override {
    return {""};
  }

  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType, int) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, std::string) const override {
    return {""};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, int) const override {
    return {""};
  }

  [[nodiscard]] bool CheckValidAffectsStmtNo(int stmt_no) const override {
    assert(stmt_no > 0);
    return true;
  }
};

class QueryOpCheckPkbFalseStub : public QueryOpCheckPkbStub {
  [[nodiscard]] bool CheckValidAffectsStmtNo(int stmt_no) const override {
    assert(stmt_no > 0);
    return false;
  }
};

TEST_CASE("Affects RHS valid stmt_no", "[QPS Parser]") {
  QueryOpCheckPkbStub pkb = QueryOpCheckPkbStub();
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::NUMBER, "1"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE_NOTHROW(QueryOperationChecker::Check(res, pkb));
}

TEST_CASE("Affects LHS valid stmt_no", "[QPS Parser]") {
  QueryOpCheckPkbStub pkb = QueryOpCheckPkbStub();
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "6"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE_NOTHROW(QueryOperationChecker::Check(res, pkb));
}

TEST_CASE("Affects LHS invalid stmt_no", "[QPS Parser]") {
  QueryOpCheckPkbFalseStub pkb = QueryOpCheckPkbFalseStub();
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::NUMBER, "5"),
                                Token(Token::COMMA),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE_THROWS(QueryOperationChecker::Check(res, pkb));
}

TEST_CASE("Affects RHS invalid stmt_no", "[QPS Parser]") {
  QueryOpCheckPkbFalseStub pkb = QueryOpCheckPkbFalseStub();
  QueryParser qp = QueryParser();
  std::vector<Token> tokens_ = {Token(Token::IDENTIFIER, "assign"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::SEMICOLON),
                                Token(Token::IDENTIFIER, "Select"),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::IDENTIFIER, "such"),
                                Token(Token::IDENTIFIER, "that"),
                                Token(Token::IDENTIFIER, "Affects"),
                                Token(Token::LEFT_ROUND_BRACKET),
                                Token(Token::IDENTIFIER, "a"),
                                Token(Token::COMMA),
                                Token(Token::NUMBER, "7"),
                                Token(Token::RIGHT_ROUND_BRACKET),
                                Token(Token::END)};
  QueryString res = qp.Parse(tokens_);

  REQUIRE_THROWS(QueryOperationChecker::Check(res, pkb));
}
