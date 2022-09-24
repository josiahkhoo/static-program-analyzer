#include <unordered_set>

#include "PKB.h"
#include "catch.hpp"
#include "common/lexer.h"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/query_parser.h"
#include "qps/query_processing_subsystem.h"

TEST_CASE("Query Processing Subsystem", "[QueryProcessingSubsystem]") {
  Lexer lexer_;

  PKB pkb;

  Planner planner_;
  Evaluator evaluator_;

  SECTION("Execute valid query - select ASSIGN") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_, pkb);

    std::string query = "assign a; Select a";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWS") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_, pkb);

    std::string query = "assign a; Select a such that Follows(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWST") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_, pkb);

    std::string query = "assign a; Select a such that Follows*(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }
}