#include <iostream>

#include "catch.hpp"
#include "qps/query_string_builder.h"

TEST_CASE("Test without 'Select' builder", "[QueryStringBuilder]") {
  QueryStringBuilder qsb = QueryStringBuilder();

  EntityReference e = EntityReference();
  e.SetWildCard();
  qsb.AddDeclaration(e);

  REQUIRE_THROWS(qsb.GetQueryString());
}

TEST_CASE("Test with 'Select' builder", "[QueryStringBuilder]") {
  QueryStringBuilder qsb = QueryStringBuilder();

  EntityReference e = EntityReference();
  e.SetWildCard();
  qsb.AddDeclaration(e);

  Select s = Select(e);
  qsb.AddSelect(s);

  REQUIRE_NOTHROW(qsb.GetQueryString());
}
