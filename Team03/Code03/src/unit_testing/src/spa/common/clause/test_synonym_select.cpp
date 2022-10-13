#include "catch.hpp"
#include "common/clause/synonym_select.h"
#include "fakeit.hpp"
#include "qps/qnodes/q_result.h"

using namespace fakeit;

TEST_CASE("Test Synonym Select", "[SynonymSelect]") {
  SECTION("Return empty when QResult is empty and have synonym") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult({}, {Synonym(EntityType::VARIABLE, "v")});
    SynonymSelect ss = SynonymSelect({Select::SynonymWithMaybeAttribute(
        Synonym(EntityType::VARIABLE, "v"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.empty());
  }
  SECTION(
      "Return empty when QResult is non-empty but does not contain SINGLE "
      "synonym") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result =
        QResult({{"123"}}, {Synonym(EntityType::VARIABLE, "v1")});
    SynonymSelect ss = SynonymSelect({Select::SynonymWithMaybeAttribute(
        Synonym(EntityType::VARIABLE, "v"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.empty());
  }
  SECTION(
      "Return empty when QResult is non-empty but does not contain all "
      "MULTIPLE synonyms") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result =
        QResult({{"123"}}, {Synonym(EntityType::VARIABLE, "v1")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v1")),
         Select::SynonymWithMaybeAttribute(
             Synonym(EntityType::VARIABLE, "v2"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.empty());
  }
  SECTION(
      "Return results when QResult is non-empty and contains selected SINGLE "
      "synonym") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult(
        {{"v11", "v21", "v31"}, {"v12", "v22", "v32"}, {"v13", "v23", "v33"}},
        {Synonym(EntityType::VARIABLE, "v1"),
         Synonym(EntityType::VARIABLE, "v2"),
         Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect({Select::SynonymWithMaybeAttribute(
        Synonym(EntityType::VARIABLE, "v1"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("v11") != res.end());
    REQUIRE(res.find("v12") != res.end());
    REQUIRE(res.find("v13") != res.end());
  }
  SECTION(
      "Return results when QResult is non-empty and contains selected MULTIPLE "
      "synonyms") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult(
        {{"v11", "v21", "v31"}, {"v12", "v22", "v32"}, {"v13", "v23", "v33"}},
        {Synonym(EntityType::VARIABLE, "v1"),
         Synonym(EntityType::VARIABLE, "v2"),
         Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v1")),
         Select::SynonymWithMaybeAttribute(
             Synonym(EntityType::VARIABLE, "v2"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("v11 v21") != res.end());
    REQUIRE(res.find("v12 v22") != res.end());
    REQUIRE(res.find("v13 v23") != res.end());
  }
  SECTION(
      "Return unique results when QResult is non-empty and contains selected "
      "MULTIPLE "
      "synonyms") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult({{"v11", "v21", "v31"},
                                {"v12", "v22", "v32"},
                                {"v11", "v21", "v33"},
                                {"v12", "v22", "v34"}},
                               {Synonym(EntityType::VARIABLE, "v1"),
                                Synonym(EntityType::VARIABLE, "v2"),
                                Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v1")),
         Select::SynonymWithMaybeAttribute(
             Synonym(EntityType::VARIABLE, "v2"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 2);
    REQUIRE(res.find("v11 v21") != res.end());
    REQUIRE(res.find("v12 v22") != res.end());
  }
  SECTION("Return mapped attribute values when attribute value != synonym") {
    Mock<QueryablePkb> queryable_pkb_stub;
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 1))
        .AlwaysReturn("x");
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 2))
        .AlwaysReturn("y");
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 3))
        .AlwaysReturn("z");
    QResult q_result =
        QResult({{"1"}, {"2"}, {"3"}}, {Synonym(EntityType::READ, "r")});
    SynonymSelect ss = SynonymSelect({Select::SynonymWithMaybeAttribute(
        Synonym(EntityType::READ, "r"), AttributeName::VAR_NAME)});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("x") != res.end());
    REQUIRE(res.find("y") != res.end());
    REQUIRE(res.find("z") != res.end());
  }
  SECTION("Return unmapped attribute values when attribute value == synonym") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult({{"v11", "v21", "v31"},
                                {"v12", "v22", "v32"},
                                {"v11", "v21", "v33"},
                                {"v12", "v22", "v34"}},
                               {Synonym(EntityType::VARIABLE, "v1"),
                                Synonym(EntityType::VARIABLE, "v2"),
                                Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v1"),
                                           AttributeName::VAR_NAME),
         Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v2"),
                                           AttributeName::VAR_NAME)});

    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 2);
    REQUIRE(res.find("v11 v21") != res.end());
    REQUIRE(res.find("v12 v22") != res.end());
  }
  SECTION("Return attribute values and non-attribute values mixed") {
    Mock<QueryablePkb> queryable_pkb_stub;
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 1))
        .AlwaysReturn("x");
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 2))
        .AlwaysReturn("y");
    When(Method(queryable_pkb_stub, QueryWithAttributeFromStatement)
             .Using(EntityType::READ, 3))
        .AlwaysReturn("z");
    QResult q_result = QResult(
        {{"1", "11"}, {"2", "12"}, {"3", "13"}},
        {Synonym(EntityType::READ, "r"), Synonym(EntityType::READ, "r1")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::READ, "r"),
                                           AttributeName::VAR_NAME),
         Select::SynonymWithMaybeAttribute(Synonym(EntityType::READ, "r1"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("x 11") != res.end());
    REQUIRE(res.find("y 12") != res.end());
    REQUIRE(res.find("z 13") != res.end());
  }
  SECTION(
      "Return results when QResult is non-empty and contains selected MULTIPLE "
      "synonyms that are the same") {
    Mock<QueryablePkb> queryable_pkb_stub;
    QResult q_result = QResult(
        {{"v11", "v21", "v31"}, {"v12", "v22", "v32"}, {"v13", "v23", "v33"}},
        {Synonym(EntityType::VARIABLE, "v1"),
         Synonym(EntityType::VARIABLE, "v2"),
         Synonym(EntityType::VARIABLE, "v3")});
    SynonymSelect ss = SynonymSelect(
        {Select::SynonymWithMaybeAttribute(Synonym(EntityType::VARIABLE, "v1")),
         Select::SynonymWithMaybeAttribute(
             Synonym(EntityType::VARIABLE, "v1"))});
    std::unordered_set<std::string> res =
        ss.GetResultSet(q_result, queryable_pkb_stub.get());
    REQUIRE(res.size() == 3);
    REQUIRE(res.find("v11 v11") != res.end());
    REQUIRE(res.find("v12 v12") != res.end());
    REQUIRE(res.find("v13 v13") != res.end());
  }
}
