#include "catch.hpp"
#include "common/clause/synonym_select.h"
#include "qps/query_string.h"

TEST_CASE("Test with 'Assign a; Select a'", "[QueryString]") {
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  QueryString qs = QueryString(s, {syn}, {});

  REQUIRE(qs.GetSynonyms().size() == 1);
  REQUIRE(qs.GetSelect()->GetSynonyms()[0] == syn);
}

TEST_CASE("Test with 'Assign a; Select a such that Follows(1, a)'",
          "[QueryString]") {
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
  QueryString qs = QueryString(s, {syn}, {f});

  REQUIRE_FALSE(std::dynamic_pointer_cast<Clause>(qs.GetQueryOperation()[0])
                    ->GetLeftHandSide()
                    .IsSynonym());
  REQUIRE(std::dynamic_pointer_cast<Clause>(qs.GetQueryOperation()[0])
              ->GetRightHandSide()
              .GetSynonym() == f->GetRightHandSide().GetSynonym());
}
