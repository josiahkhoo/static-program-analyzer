#include "catch.hpp"
#include "fakeit.hpp"
#include "sp/extractor/abstraction_extractor_impl.h"
using namespace fakeit;

TEST_CASE("Abstraction Extractor", "[AbstractionExtractor]") {
  Mock<FollowsAbstractionExtractor> follows_abstraction_extractor;
  When(Method(follows_abstraction_extractor, Extract)).AlwaysReturn({});
  Mock<FollowsTAbstractionExtractor> follows_t_abstraction_extractor;
  When(Method(follows_t_abstraction_extractor, Extract)).AlwaysReturn({});
  AbstractionExtractorImpl extractor_under_test =
      AbstractionExtractorImpl(follows_abstraction_extractor.get(),
                               follows_t_abstraction_extractor.get());
  SECTION("Extracts respective entities") {
    std::vector<AssignEntity> assign_entities = {};
    std::vector<CallEntity> call_entities = {};
    std::vector<ConstantEntity> constant_entities = {};
    std::vector<IfEntity> if_entities = {};
    std::vector<PrintEntity> print_entities = {};
    std::vector<ProcedureEntity> procedure_entities = {};
    std::vector<ReadEntity> read_entities = {};
    std::vector<StatementEntity> statement_entities = {};
    std::vector<VariableEntity> variable_entities = {};
    std::vector<WhileEntity> while_entities = {};
    AbstractionExtractorResult res = extractor_under_test.Extract(
        assign_entities, call_entities, constant_entities, if_entities,
        print_entities, procedure_entities, read_entities, statement_entities,
        variable_entities, while_entities);

    Verify(Method(follows_abstraction_extractor, Extract)).Once();
    Verify(Method(follows_t_abstraction_extractor, Extract)).Once();
  }
}