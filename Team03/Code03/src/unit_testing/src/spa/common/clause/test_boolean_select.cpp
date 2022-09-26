#include "catch.hpp"
#include "common/clause/boolean_select.h"
#include "qps/qnodes/q_result.h"

TEST_CASE("Test Boolean Select", "[BooleanSelect]") {
  SECTION("Return false when QResult is empty") {
    QResult q_result = QResult({}, {Synonym(EntityType::VARIABLE, "v")});
    BooleanSelect bs = BooleanSelect();
    std::unordered_set<std::string> res = bs.GetResultSet(q_result);
    REQUIRE(res.size() == 1);
    REQUIRE(res.find("FALSE") != res.end());
  }
  SECTION("Return true when QResult is non-empty") {
    QResult q_result = QResult({{"v1"}}, {Synonym(EntityType::VARIABLE, "v")});
    BooleanSelect bs = BooleanSelect();
    std::unordered_set<std::string> res = bs.GetResultSet(q_result);
    REQUIRE(res.find("TRUE") != res.end());
  }
}
