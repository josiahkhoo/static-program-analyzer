#include "catch.hpp"
#include "common/clause/affects_clause.h"
#include "common/clause/synonym_select.h"
#include "qps/query_operation_checker.h"
#include "qps/query_parser.h"

class QueryOpCheckPkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType) const override {
    return {"QueryAll"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType) const override {
    return {"QueryAllFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType) const override {
    return {"QueryAllFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int, EntityType) const override {
    return {"QueryFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int, EntityType) const override {
    return {"QueryFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int, EntityType) const override {
    return {"QueryFollowsT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int, EntityType) const override {
    return {"QueryFollowsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType) const override {
    return {"QueryAllParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType) const override {
    return {"QueryAllParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int, EntityType) const override {
    return {"QueryParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int, EntityType) const override {
    return {"QueryParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int, EntityType) const override {
    return {"QueryParentT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int, EntityType) const override {
    return {"QueryParentTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType) const override {
    return {"QueryAllUses"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType) const override {
    return {"QueryAllUsesBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int, EntityType) const override {
    return {"QueryUsesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string, EntityType) const override {
    return {"QueryUsesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string, EntityType) const override {
    return {"QueryUsesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string, EntityType) const override {
    return {"QueryUsesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType) const override {
    return {"QueryAllModifies"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType) const override {
    return {"QueryAllModifiesBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int) const override {
    return {"QueryModifiesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string, EntityType) const override {
    return {"QueryModifiesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string) const override {
    return {"QueryModifiesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string) const override {
    return {"QueryModifiesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls() const override {
    return {"QueryAllCalls"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy()
      const override {
    return {"QueryAllCallsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string) const override {
    return {"QueryCalls"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string) const override {
    return {"QueryCallsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string) const override {
    return {"QueryCallsT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string) const override {
    return {"QueryCallsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllNext(
      EntityType) const override {
    return {"QueryAllNext"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllPrevious(
      EntityType) const override {
    return {"QueryAllPrevious"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryNext(
      int, EntityType) const override {
    return {"QueryNext"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPrevious(
      int, EntityType) const override {
    return {"QueryPrevious"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryNextT(
      int, EntityType) const override {
    return {"QueryNextT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPreviousT(
      int, EntityType) const override {
    return {"QueryPreviousT"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllAffects()
      const override {
    return {"QueryAllAffects"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllAffectsBy()
      const override {
    return {"QueryAllAffectsBy"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffects(
      int) const override {
    return {"QueryAffects"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsBy(
      int) const override {
    return {"QueryAffectsBy"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsT(
      int) const override {
    return {"QueryAffectsT"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAffectsTBy(
      int) const override {
    return {"QueryAffectsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression) const override {
    return {"QueryAllAssignPattern"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string, Expression) const override {
    return {"QueryPatternStr"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const override {
    return {"QueryAllFollowsRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const override {
    return {"QueryAllParentsRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations()
      const override {
    return {"QueryAllCallsRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllNextRelations()
      const override {
    return {"QueryAllNextRelations"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllWhilePattern()
      const override {
    return {"QueryAllWhilePattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryWhilePattern(
      std::string) const override {
    return {"QueryWhilePattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllIfPattern()
      const override {
    return {"QueryAllIfPattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryIfPattern(
      std::string) const override {
    return {"QueryIfPattern"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int) const override {
    return {"QueryPatternVariablesFromAssign"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int) const override {
    return {"QueryPatternVariablesFromWhile"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int) const override {
    return {"QueryPatternVariablesFromIf"};
  }

  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType, int) const override {
    return {"QueryWithAttributeFromStatement"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, std::string) const override {
    return {"QueryWithAttributeIdentifier"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, int) const override {
    return {"QueryWithAttributeNumber"};
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

  QueryOperationChecker::Check(res, pkb);
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

  QueryOperationChecker::Check(res, pkb);
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
