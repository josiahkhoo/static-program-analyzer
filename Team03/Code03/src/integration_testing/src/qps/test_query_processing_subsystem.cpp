#include <unordered_set>

#include "catch.hpp"
#include "common/lexer.h"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/query_parser.h"
#include "qps/query_processing_subsystem.h"

TEST_CASE("Query Processing Subsystem", "[QueryProcessingSubsystem]") {
  Lexer lexer_;

  class QueryablePkbStub : public QueryablePkb {
   public:
    [[nodiscard]] std::unordered_set<std::string> QueryAll(
        EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollow(
        EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowBy(
        EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollow(
        int statement_number, EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowBy(
        int statement_number, EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowT(
        int statement_number, EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowTBy(
        int statement_number, EntityType type) const override {
      return {"1"};
    }
  };

  QueryablePkbStub queryable_pkb_stub_;

  Planner planner_;
  Evaluator evaluator_;

  SECTION("Execute valid query - select ASSIGN") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 queryable_pkb_stub_);

    std::string query = "assign a; Select a";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWS") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 queryable_pkb_stub_);

    std::string query = "assign a; Select a such that Follows(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }

  SECTION("Execute valid query - select ASSIGN and FOLLOWST") {
    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                                 queryable_pkb_stub_);

    std::string query = "assign a; Select a such that Follows*(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }
}