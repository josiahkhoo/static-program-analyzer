#include "catch.hpp"
#include "qps/query_string.h"

TEST_CASE("Test with 'Assign a; Select a'", "[QueryString]") {
  EntityReference e = EntityReference();
  e.SetSynonym("a");
  std::vector<EntityReference> declared = {e};

  Select s = Select(e);
  QueryString qs = QueryString(s, declared, {});

  REQUIRE(qs.GetEntities().size() == 1);
  REQUIRE(qs.GetSelect().GetEntity().GetSynonym() == "a");
}

TEST_CASE("Test with 'Assign a; Select a such that Follows(1, a)'",
          "[QueryString]") {
  EntityReference e = EntityReference();
  e.SetSynonym("a");
  Select s = Select(e);
  StatementReference stmtRef1, stmtRef2 = StatementReference();
  stmtRef1.SetLineNumber("1");
  stmtRef2.SetSynonym("a");
  FollowsClause f = FollowsClause(stmtRef1, stmtRef2);

  QueryString qs = QueryString(s, {}, {f});

  REQUIRE_FALSE(qs.GetClause()[0].GetLeftHandSide().IsSynonym());
  REQUIRE(qs.GetClause()[0].GetRightHandSide().GetSynonym() == f.GetRightHandSide().GetSynonym());
}
