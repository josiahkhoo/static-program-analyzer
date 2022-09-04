#include "catch.hpp"
#include "common/queryable_pkb.h"
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

TEST_CASE("Test construct 1 node: Select", "[Planner]") {
  Planner p = Planner();

  EntityReference e = EntityReference();
  e.SetSynonym("a");
  Select s = Select(e);
  QueryString qs = QueryString(s, {}, {});

  QNode* root = p.Plan(qs);
  REQUIRE(root->IsLeaf());
}

TEST_CASE("Test construct 1 node: Select & Follows", "[Planner]") {
  Planner p = Planner();

  EntityReference e = EntityReference();
  e.SetSynonym("a");
  Select s = Select(e);
  StatementReference stmtRef1, stmtRef2 = StatementReference();
  stmtRef1.SetLineNumber("1");
  stmtRef2.SetSynonym("a");
  FollowsClause f = FollowsClause(stmtRef1, stmtRef2);
  QueryString qs = QueryString(s, {}, {f});

  QNode* root = p.Plan(qs);
  REQUIRE(root->IsLeaf());
}

TEST_CASE("Test query 1 node: Select & Follows", "[Planner]") {
  Planner p = Planner();

  EntityReference e = EntityReference();
  e.SetSynonym("a");
  Select s = Select(e);
  StatementReference stmtRef1, stmtRef2 = StatementReference();
  stmtRef1.SetLineNumber("1");
  stmtRef2.SetSynonym("a");
  FollowsClause f = FollowsClause(stmtRef1, stmtRef2);
  QueryString qs = QueryString(s, {}, {f});
  QNode* root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(root->Fetch(pkb).size() == 1);
}
