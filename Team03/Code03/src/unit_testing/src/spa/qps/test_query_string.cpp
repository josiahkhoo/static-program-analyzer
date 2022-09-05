#include "catch.hpp"
#include "qps/query_string.h"

TEST_CASE("Test with 'Assign a; Select a'", "[QueryString]") {
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  QueryString qs = QueryString(s, {syn}, {});

  REQUIRE(qs.GetSynonyms().size() == 1);
  REQUIRE(qs.GetSelect().GetSynonym() == syn);
}

TEST_CASE("Test with 'Assign a; Select a such that Follows(1, a)'",
          "[QueryString]") {
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  FollowsClause f = FollowsClause(statement_ref_1, statement_ref_2);
  QueryString qs = QueryString(s, {syn}, {f});

  REQUIRE_FALSE(qs.GetClause()[0].GetLeftHandSide().IsSynonym());
  REQUIRE(qs.GetClause()[0].GetRightHandSide().GetSynonym() ==
          f.GetRightHandSide().GetSynonym());
}
