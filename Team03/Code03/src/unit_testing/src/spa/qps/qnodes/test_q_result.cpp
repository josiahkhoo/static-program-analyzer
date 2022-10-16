#include "catch.hpp"
#include "qps/qnodes/q_result.h"

TEST_CASE("Query Result", "[QResult]") {
  SECTION(
      "Join 1 empty with no synonym QResult and 1 non-empty QResult returns "
      "the non-empty "
      "QResult") {
    QResult empty_res = QResult({}, {});
    QResult non_empty_res =
        QResult({{"1"}, {"2"}}, {Synonym(EntityType::ASSIGN, "a")});
    QResult res = empty_res.Join(non_empty_res);
    REQUIRE(res == non_empty_res);

    res = non_empty_res.Join(empty_res);
    REQUIRE(res == non_empty_res);
  }

  SECTION(
      "Join 1 empty with synonym QResult and 1 non-empty QResult returns empty "
      "QResult with both synonyms") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a1");
    Synonym syn2 = Synonym(EntityType::ASSIGN, "a2");
    QResult empty_res_with_syn = QResult({}, {syn1});
    QResult non_empty_res = QResult({{"1"}, {"2"}}, {syn2});

    QResult expected = QResult({}, {syn1, syn2});
    QResult res = empty_res_with_syn.Join(non_empty_res);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are disjoint and "
      "separate entity types returns all combination QResult") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::READ, "r");
    QResult res1 = QResult({{"3"}, {"4"}}, {syn1});
    QResult res2 = QResult({{"1"}, {"2"}}, {syn2});

    QResult expected =
        QResult({{"3", "1"}, {"3", "2"}, {"4", "1"}, {"4", "2"}}, {syn1, syn2});
    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are disjoint but "
      "share same entity types returns all combination") {
    Synonym syn1 = Synonym(EntityType::VARIABLE, "v1");
    Synonym syn2 = Synonym(EntityType::VARIABLE, "v2");
    QResult res1 = QResult({{"x"}, {"y"}}, {syn1});
    QResult res2 = QResult({{"x"}, {"y"}}, {syn2});

    QResult expected =
        QResult({{"x", "x"}, {"x", "y"}, {"y", "x"}, {"y", "y"}}, {syn1, syn2});
    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are disjoint but "
      "one is statement and one is assign can return the same") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::STATEMENT, "r");
    QResult res1 = QResult({{"3"}, {"4"}}, {syn1});
    QResult res2 = QResult({{"1"}, {"2"}, {"3"}, {"4"}}, {syn2});

    QResult expected = QResult({{"3", "1"},
                                {"3", "2"},
                                {"3", "3"},
                                {"3", "4"},
                                {"4", "1"},
                                {"4", "2"},
                                {"4", "3"},
                                {"4", "4"}},
                               {syn1, syn2});
    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are disjoint with "
      "multiple vars each") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
    Synonym syn3 = Synonym(EntityType::READ, "r");
    Synonym syn4 = Synonym(EntityType::CONSTANT, "cs");
    QResult res1 = QResult({{"3", "x"}, {"4", "y"}}, {syn1, syn2});
    QResult res2 = QResult(
        {{"11", "20"}, {"12", "21"}, {"13", "22"}, {"14", "23"}}, {syn3, syn4});

    QResult expected = QResult({{"3", "x", "11", "20"},
                                {"3", "x", "12", "21"},
                                {"3", "x", "13", "22"},
                                {"3", "x", "14", "23"},
                                {"4", "y", "11", "20"},
                                {"4", "y", "12", "21"},
                                {"4", "y", "13", "22"},
                                {"4", "y", "14", "23"}},
                               {syn1, syn2, syn3, syn4});
    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are joined by 1 "
      "var") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
    Synonym syn3 = Synonym(EntityType::READ, "r");
    QResult res1 = QResult({{"3", "y"}, {"4", "x"}}, {syn1, syn2});
    QResult res2 =
        QResult({{"y", "1"}, {"y", "2"}, {"x", "1"}, {"x", "2"}, {"z", "5"}},
                {syn2, syn3});
    QResult expected = QResult(
        {{"3", "y", "1"}, {"3", "y", "2"}, {"4", "x", "1"}, {"4", "x", "2"}},
        {syn1, syn2, syn3});

    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION(
      "Join 1 non-empty QResult and 1 non-empty QResult that are joined by 3 "
      "var") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
    Synonym syn3 = Synonym(EntityType::READ, "r");
    Synonym syn4 = Synonym(EntityType::CONSTANT, "cs");
    Synonym syn5 = Synonym(EntityType::CALL, "c");
    QResult res1 = QResult({{"3", "y", "13", "1"},
                            {"2", "y", "13", "1"},
                            {"4", "x", "14", "2"},
                            {"5", "z", "15", "3"}},
                           {syn1, syn2, syn3, syn4});
    QResult res2 = QResult({{"y", "13", "1", "31"},
                            {"y", "13", "1", "35"},
                            {"x", "14", "2", "32"},
                            {"p", "15", "3", "33"}},
                           {syn2, syn3, syn4, syn5});
    QResult expected = QResult({{"3", "y", "13", "1", "31"},
                                {"2", "y", "13", "1", "31"},
                                {"3", "y", "13", "1", "35"},
                                {"2", "y", "13", "1", "35"},
                                {"4", "x", "14", "2", "32"}},
                               {syn1, syn2, syn3, syn4, syn5});

    QResult res = res1.Join(res2);

    REQUIRE(res == expected);
  }

  SECTION("Intersect two QResults") {
    Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
    Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
    QResult res1 = QResult({{"3", "x"}, {"4", "y"}}, {syn1, syn2});
    QResult res2 = QResult({{"2", "z"}, {"3", "x"}}, {syn1, syn2});

    QResult res = res1.Join(res2);
    QResult expected = QResult({{"3", "x"}}, {syn1, syn2});

    REQUIRE(res == expected);
  }
}

TEST_CASE("qwe", "[QResults]") {
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
  Synonym syn2 = Synonym(EntityType::READ, "r");
  QResult res1 = QResult({{"3"}, {"4"}}, {syn1});
  QResult res2 = QResult({{"1"}, {"2"}}, {syn2});

  QResult expected =
      QResult({{"3", "1"}, {"3", "2"}, {"4", "1"}, {"4", "2"}}, {syn1, syn2});
  QResult res = res1.Join(res2);

  REQUIRE(res == expected);
}

TEST_CASE("asd") {
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
  Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
  Synonym syn3 = Synonym(EntityType::READ, "r");
  QResult res1 = QResult({{"3", "y"}, {"4", "x"}}, {syn1, syn2});
  QResult res2 =
      QResult({{"y", "1"}, {"y", "2"}, {"x", "1"}, {"x", "2"}, {"z", "5"}},
              {syn2, syn3});
  QResult expected = QResult(
      {{"3", "y", "1"}, {"3", "y", "2"}, {"4", "x", "1"}, {"4", "x", "2"}},
      {syn1, syn2, syn3});

  QResult res = res1.Join(res2);

  REQUIRE(res == expected);
}

TEST_CASE(
    "Join 1 non-empty QResult and 1 non-empty QResult that are joined by 3 "
    "var") {
  Synonym syn1 = Synonym(EntityType::ASSIGN, "a");
  Synonym syn2 = Synonym(EntityType::VARIABLE, "v");
  Synonym syn3 = Synonym(EntityType::READ, "r");
  Synonym syn4 = Synonym(EntityType::CONSTANT, "cs");
  Synonym syn5 = Synonym(EntityType::CALL, "c");
  QResult res1 = QResult({{"3", "y", "13", "1"},
                          {"2", "y", "13", "1"},
                          {"4", "x", "14", "2"},
                          {"5", "z", "15", "3"}},
                         {syn1, syn2, syn3, syn4});
  QResult res2 = QResult({{"y", "13", "1", "31"},
                          {"y", "13", "1", "35"},
                          {"x", "14", "2", "32"},
                          {"p", "15", "3", "33"}},
                         {syn2, syn3, syn4, syn5});
  QResult expected = QResult({{"3", "y", "13", "1", "31"},
                              {"3", "y", "13", "1", "35"},
                              {"2", "y", "13", "1", "31"},
                              {"2", "y", "13", "1", "35"},
                              {"4", "x", "14", "2", "32"}},
                             {syn1, syn2, syn3, syn4, syn5});

  QResult res = res1.Join(res2);

  REQUIRE(res == expected);
}