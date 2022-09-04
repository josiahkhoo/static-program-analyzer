#include <iostream>

#include "catch.hpp"
#include "qps/evaluator.h"
#include "qps/planner.h"

class QueryablePkbStub : public QueryablePkb {
 public:
  std::vector<std::string> query(EntityReference t) override { return {"1"}; };

  std::vector<std::string> query(Clause t) override { return {"1"}; };

  std::vector<std::string> query(AssignEntity t) override { return {"1"}; };

  std::vector<std::string> query(FollowsClause t) override { return {"1"}; };

  std::vector<std::string> query(FollowsTClause t) override { return {"1"}; };
};

TEST_CASE("Query Select", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  EntityReference e = EntityReference();
  e.SetSynonym("a");
  Select s = Select(e);
  QueryString qs = QueryString(s, {}, {});
  QNode* root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::vector<std::string> expected = pkb.query(e);
  std::vector<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}
