#include <iostream>

#include "catch.hpp"
#include "common/clause/synonym_select.h"
#include "qps/query_string_builder.h"

TEST_CASE("Test without 'Select' builder", "[QueryStringBuilder]") {
  QueryStringBuilder qsb = QueryStringBuilder();

  REQUIRE(qsb.HasNoSelect());
}

TEST_CASE("Test with 'Select' builder", "[QueryStringBuilder]") {
  QueryStringBuilder qsb = QueryStringBuilder();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});

  qsb.AddDeclaration(syn);
  qsb.AddSelect(s);

  REQUIRE_NOTHROW(qsb.GetQueryString());
}
