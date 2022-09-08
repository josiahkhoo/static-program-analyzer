#include <iostream>

#include "catch.hpp"
#include "qps/evaluator.h"
#include "qps/planner.h"

class QueryablePkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override {
    return {"1"};
  }
};

TEST_CASE("Query Select", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  QueryString qs = QueryString(s, {syn}, {});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAll(EntityType::ASSIGN);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}