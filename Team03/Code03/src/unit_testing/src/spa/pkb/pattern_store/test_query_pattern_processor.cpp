#include "catch.hpp"
#include "pkb/pattern_store/query_pattern_processor.h"

TEST_CASE("Assign Pattern Bracketization", "[QueryPatternProcessor]") {
  QueryPatternProcessor processor;

  std::string test_pattern_1 = "x+y+z";
  std::string processed_pattern_1 = "(((x)+(y))+(z))";
  REQUIRE(processed_pattern_1.compare(
              processor.ProcessAssignPattern(test_pattern_1)) == 0);

  std::string test_pattern_2 = "x*y/z";
  std::string processed_pattern_2 = "(((x)*(y))/(z))";
  REQUIRE(processed_pattern_2.compare(
              processor.ProcessAssignPattern(test_pattern_2)) == 0);

  std::string test_pattern_3 = "x+y*z";
  std::string processed_pattern_3 = "((x)+((y)*(z)))";
  REQUIRE(processed_pattern_3.compare(
              processor.ProcessAssignPattern(test_pattern_3)) == 0);

  std::string test_pattern_4 = "v-x*y+z*t";
  std::string processed_pattern_4 = "(((v)-((x)*(y)))+((z)*(t)))";
  REQUIRE(processed_pattern_4.compare(
              processor.ProcessAssignPattern(test_pattern_4)) == 0);
}
