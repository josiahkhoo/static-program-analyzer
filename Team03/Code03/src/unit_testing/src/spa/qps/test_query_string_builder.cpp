#include <iostream>

#include "catch.hpp"
#include "qps/query_string_builder.h"

TEST_CASE("Test without 'Select' builder", "[QueryStringBuilder]") {
    QueryStringBuilder qsb = QueryStringBuilder();

    REQUIRE_THROWS(qsb.GetQueryString());
}

TEST_CASE("Test with 'Select' builder", "[QueryStringBuilder]") {
    QueryStringBuilder qsb = QueryStringBuilder();

    Synonym syn = Synonym(EntityType::ASSIGN, "a");
    Select s = Select(syn);

    qsb.AddDeclaration(syn);
    qsb.AddSelect(s);

    REQUIRE_NOTHROW(qsb.GetQueryString());
}
