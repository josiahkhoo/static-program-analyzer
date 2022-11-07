#include <unordered_set>

#include "catch.hpp"
#include "common/lexer.h"
#include "pkb/pkb.h"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/query_parser.h"
#include "qps/query_processing_subsystem.h"

TEST_CASE("Query Processing Subsystem", "[QueryProcessingSubsystem]") {
  Lexer lexer_;

  EntityManager entity_manager_;
  RelationshipManager relationship_manager_;
  PatternManager pattern_manager_;
  QueryablePkbFacade queryable_pkb_facade_ = QueryablePkbFacade(
      entity_manager_, relationship_manager_, pattern_manager_);
  StorablePkbFacade storable_pkb_facade_ = StorablePkbFacade(
      entity_manager_, relationship_manager_, pattern_manager_);
  PKB pkb_ = PKB(storable_pkb_facade_, queryable_pkb_facade_);

  Planner planner_;
  Evaluator evaluator_;

  SECTION("Execute valid query - select ASSIGN") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 pkb_);

    std::string query = "assign a; Select a";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWS") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 pkb_);

    std::string query = "assign a; Select a such that Follows(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWST") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 pkb_);

    std::string query = "assign a; Select a such that Follows*(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }
}