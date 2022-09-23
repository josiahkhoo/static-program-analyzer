#include "catch.hpp"
#include "common/clause/synonym_select.h"
#include "qps/qnodes/q_result.h"

TEST_CASE("Test Synonym Select", "[SynonymSelect]") {
  SECTION("Return empty when QResult is empty and have synonym") {
    QResult q_result = QResult({}, {Synonym(EntityType::VARIABLE, "v")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.empty());
  }
  SECTION(
      "Return empty when QResult is non-empty but does not contain SINGLE "
      "synonym") {
    QResult q_result =
        QResult({{"123"}}, {Synonym(EntityType::VARIABLE, "v1")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.empty());
  }
  SECTION(
      "Return empty when QResult is non-empty but does not contain all "
      "MULTIPLE synonyms") {
    QResult q_result =
        QResult({{"123"}}, {Synonym(EntityType::VARIABLE, "v1")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v1"),
                                      Synonym(EntityType::VARIABLE, "v2")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.empty());
  }
  SECTION(
      "Return results when QResult is non-empty and contains selected SINGLE "
      "synonym") {
    QResult q_result = QResult(
        {{"v11", "v21", "v31"}, {"v12", "v22", "v32"}, {"v13", "v23", "v33"}},
        {Synonym(EntityType::VARIABLE, "v1"),
         Synonym(EntityType::VARIABLE, "v2"),
         Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v1")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("v11") != res.end());
    REQUIRE(res.find("v12") != res.end());
    REQUIRE(res.find("v13") != res.end());
  }
  SECTION(
      "Return results when QResult is non-empty and contains selected MULTIPLE "
      "synonyms") {
    QResult q_result = QResult(
        {{"v11", "v21", "v31"}, {"v12", "v22", "v32"}, {"v13", "v23", "v33"}},
        {Synonym(EntityType::VARIABLE, "v1"),
         Synonym(EntityType::VARIABLE, "v2"),
         Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v1"),
                                      Synonym(EntityType::VARIABLE, "v2")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("v11 v21") != res.end());
    REQUIRE(res.find("v12 v22") != res.end());
    REQUIRE(res.find("v13 v23") != res.end());
  }
  SECTION(
      "Return unique results when QResult is non-empty and contains selected "
      "MULTIPLE "
      "synonyms") {
    QResult q_result = QResult({{"v11", "v21", "v31"},
                                {"v12", "v22", "v32"},
                                {"v11", "v21", "v33"},
                                {"v12", "v22", "v34"}},
                               {Synonym(EntityType::VARIABLE, "v1"),
                                Synonym(EntityType::VARIABLE, "v2"),
                                Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect({Synonym(EntityType::VARIABLE, "v1"),
                                      Synonym(EntityType::VARIABLE, "v2")});
    std::unordered_set<std::string> res = ss.GetResultSet(q_result);
    REQUIRE(res.size() == 2);
    REQUIRE(res.find("v11 v21") != res.end());
    REQUIRE(res.find("v12 v22") != res.end());
  }
}
