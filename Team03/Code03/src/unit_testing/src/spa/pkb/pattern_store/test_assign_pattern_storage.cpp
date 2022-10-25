#include "catch.hpp"
#include "pkb/pattern_store/assign_pattern_storage.h"

TEST_CASE("Get All Pattern Search", "[AssignPatternStorage]") {
  AssignPatternStorage storage;
  storage.AddAssignPattern(1, "var1", "((x)*(y))");
  storage.AddAssignPattern(2, "var2", "(((x)*(y))+(z))");
  storage.AddAssignPattern(3, "var3", "((z)+((x)*(y)))");
  storage.AddAssignPattern(4, "var4", "(((z)+((x)*(y)))+(z))");
  storage.AddAssignPattern(5, "var5", "(t)");

  std::unordered_set<std::string> res =
      storage.GetAllPattern("NoPattern", false, false);
  REQUIRE(res.empty());

  std::unordered_set<std::string> res1 =
      storage.GetAllPattern("((x)*(y))", false, false);
  std::unordered_set<std::string> test1 = {"1"};
  REQUIRE(res1 == test1);

  std::unordered_set<std::string> res2 =
      storage.GetAllPattern("((x)*(y))", true, true);
  std::unordered_set<std::string> test2 = {"1", "2", "3", "4"};
  REQUIRE(res2 == test2);

  std::unordered_set<std::string> res3 =
      storage.GetAllPattern("((x)*(y))", true, true);
  std::unordered_set<std::string> test3 = {"1", "2", "3", "4"};
  REQUIRE(res3 == test3);

  std::unordered_set<std::string> res4 =
      storage.GetAllPattern("(z)", true, true);
  std::unordered_set<std::string> test4 = {"2", "3", "4"};
  REQUIRE(res4 == test4);

  std::unordered_set<std::string> res5 =
      storage.GetAllPattern("((z)+((x)*(y)))", true, true);
  std::unordered_set<std::string> test5 = {"3", "4"};
  REQUIRE(res5 == test5);

  std::unordered_set<std::string> res7 =
      storage.GetAllPattern("(z)", false, false);
  REQUIRE(res7.empty());

  std::unordered_set<std::string> res8 =
      storage.GetAllPattern("(((x)*(y))+(z))", true, true);
  std::unordered_set<std::string> test8 = {"2"};
  REQUIRE(res8 == test8);

  std::unordered_set<std::string> res9 = storage.GetAllPattern("", true, true);
  std::unordered_set<std::string> test9 = {"1", "2", "3", "4", "5"};
  REQUIRE(res9 == test9);
}

TEST_CASE("Get Pattern Search", "[AssignPatternStorage]") {
  AssignPatternStorage storage;
  storage.AddAssignPattern(1, "var1", "((x)*(y))");
  storage.AddAssignPattern(2, "var1", "(((x)*(y))+(z))");
  storage.AddAssignPattern(3, "var2", "((x)*(y))");
  storage.AddAssignPattern(4, "var2", "(((x)*(y))+(z))");

  std::unordered_set<std::string> res =
      storage.GetPattern("NoLHS", "NoPattern", false, false);
  REQUIRE(res.empty());

  std::unordered_set<std::string> res1 =
      storage.GetPattern("NoLHS", "((x)*(y))", false, false);
  REQUIRE(res1.empty());

  std::unordered_set<std::string> res2 =
      storage.GetPattern("var1", "((x)*(y))", true, true);
  std::unordered_set<std::string> test2 = {"1", "2"};
  REQUIRE(res2 == test2);

  std::unordered_set<std::string> res3 =
      storage.GetPattern("var2", "((x)*(y))", true, true);
  std::unordered_set<std::string> test3 = {"3", "4"};
  REQUIRE(res3 == test3);

  std::unordered_set<std::string> res4 =
      storage.GetPattern("var1", "(z)", true, true);
  std::unordered_set<std::string> test4 = {"2"};
  REQUIRE(res4 == test4);
}
