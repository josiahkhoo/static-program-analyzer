#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "catch.hpp"
#include "spa.h"

std::string ltrim(const std::string& s) {
  return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
  return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) { return ltrim(rtrim(s)); }

void ExecuteTest(SPA& spa, const std::string& sub_test_name,
                 const std::string& query,
                 const std::string& expected_results) {
  SECTION(sub_test_name) {
    std::list<std::string> results;
    spa.Evaluate(query, results);

    std::set<std::string> result_set;
    for (const auto& result : results) {
      result_set.insert(result);
    }

    std::set<std::string> expected_result_set;
    std::stringstream expected_results_stream =
        std::stringstream(expected_results);

    while (expected_results_stream.good()) {
      std::string substr;
      getline(expected_results_stream, substr, ',');
      substr = trim(substr);
      if (!substr.empty()) {
        expected_result_set.insert(substr);
      }
    }
    REQUIRE(result_set == expected_result_set);
  }
}

enum MODULO_TEST {
  SUB_TEST_NAME = 0,
  QUERY_DECLARATION = 1,
  QUERY_ACTUAL = 2,
  EXPECTED_RES = 3,
  TIME_LIMIT = 4
};

TEST_CASE("SPA", "[SPA]") {
  std::vector<std::pair<std::string, std::string>> test_cases = {
      // Milestone 1
      {"Entities Only", "entities_only"},
      {"Follows / FollowsT", "follows_follows_t"},
      {"Semantic Errors", "semantic_errors"},
      {"Syntax Errors", "syntax_errors"},
      {"Assign Patterns only", "assign_patterns_only"},
      {"Parent / ParentT", "parent_parent_t"},
      {"Uses Procedure", "uses_p"},
      {"Uses Statement", "uses_s"},
      {"Modifies Procedure", "modifies_p"},
      {"Modifies Statement", "modifies_s"},
      {"Clause and Pattern", "clause_and_pattern"},
      {"Parse weird source", "parse_weird_source"},
      {"Parse conditional source", "parse_conditional_source"},
      // Milestone 2
      {"Source Error: Call non-existing procedure",
       "source_error_call_non_existing_procedure"},
      {"Source Error: Cyclic procedure call", "source_error_cyclic_call"},
      {"Source Error: Recursive procedure call", "source_error_recursive_call"},
      {"Source Error: Two procedure same name",
       "source_error_two_procedure_same_name"},
      {"Uses Statement with Calls", "uses_s_with_call"},
      {"Uses Procedure with Calls", "uses_p_with_call"},
      {"Modifies Statement with Calls", "modifies_s_with_call"},
      {"Modifies Procedure with Calls", "modifies_p_with_call"},
      {"Boolean select", "boolean_select"},
      {"Calls / Calls T", "calls_calls_t"},
      {"If Patterns only", "if_patterns_only"},
      {"While Patterns only", "while_patterns_only"},
      {"With only", "with_only"},
      {"And and With", "and_with"},
      {"Select attribute", "select_attribute"},
      {"Tuple select", "tuple_select"},
      //      {"Next / Next T", "next_next_t"}
  };
  for (auto [test_name, file_prefix] : test_cases) {
    std::string test_folder = std::getenv("TEST_FOLDER");
    std::string os = std::getenv("OS");
    std::string path_seperator = (os == "win") ? "\\" : "/";
    std::string source_file_name = test_folder;
    std::string query_file_name = test_folder;
    source_file_name = source_file_name.append(path_seperator)
                           .append(file_prefix)
                           .append(path_seperator)
                           .append("test_")
                           .append(file_prefix)
                           .append("_source.txt");
    query_file_name = query_file_name.append(path_seperator)
                          .append(file_prefix)
                          .append(path_seperator)
                          .append("test_")
                          .append(file_prefix)
                          .append("_queries.txt");
    SECTION("Test " + test_name) {
      SPA spa_under_test;
      spa_under_test.Parse(source_file_name);

      std::string line;
      std::ifstream query_file = std::ifstream(query_file_name);
      int line_number = 0;
      std::string sub_test_name, query, expected_results;
      if (query_file.is_open()) {
        while (getline(query_file, line)) {
          switch (line_number % 5) {
            case SUB_TEST_NAME:
              sub_test_name = line;
              break;
            case QUERY_DECLARATION:
            case QUERY_ACTUAL:
              query.append(line);
              break;
            case EXPECTED_RES:
              expected_results = line;
              break;
            case TIME_LIMIT:
              ExecuteTest(spa_under_test, sub_test_name, query,
                          expected_results);
              // Reset
              sub_test_name = "";
              query = "";
              expected_results = "";
              break;
          }
          line_number++;
        }
        query_file.close();
      }
    }
  }
}