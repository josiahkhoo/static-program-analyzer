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

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollow(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowBy(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollow(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowBy(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowT(
      int statement_number, EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowTBy(
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
  QNode* root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAll(EntityType::ASSIGN);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}
