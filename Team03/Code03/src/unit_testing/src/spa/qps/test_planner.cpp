#include "catch.hpp"
#include "common/queryable_pkb.h"
#include "qps/planner.h"

class QueryablePkbStub : public QueryablePkb {
 public:
  std::vector<std::string> query(EntityReference t) override { return {"1"}; };

  std::vector<std::string> query(Clause t) override { return {"1"}; };

  std::vector<std::string> query(AssignEntity t) override { return {"1"}; };

  std::vector<std::string> query(FollowsClause t) override { return {"1"}; };

  std::vector<std::string> query(FollowsTClause t) override { return {"1"}; };
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
