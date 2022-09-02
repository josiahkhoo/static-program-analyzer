#include "catch.hpp"
#include "common/lexer.h"
#include "sp/extractor/abstraction/follows_abstraction_extractor.h"
#include "sp/extractor/abstraction/follows_t_abstraction_extractor.h"
#include "sp/extractor/abstraction_extractor_impl.h"
#include "sp/extractor/design_extractor_impl.h"
#include "sp/extractor/entity/assign_entity_node_extractor.h"
#include "sp/extractor/entity/call_entity_node_extractor.h"
#include "sp/extractor/entity/constant_entity_node_extractor.h"
#include "sp/extractor/entity/if_entity_node_extractor.h"
#include "sp/extractor/entity/print_entity_node_extractor.h"
#include "sp/extractor/entity/procedure_entity_node_extractor.h"
#include "sp/extractor/entity/read_entity_node_extractor.h"
#include "sp/extractor/entity/statement_entity_node_extractor.h"
#include "sp/extractor/entity/variable_entity_node_extractor.h"
#include "sp/extractor/entity/while_entity_node_extractor.h"
#include "sp/extractor/entity_extractor_impl.h"
#include "sp/simple_parser.h"
#include "sp/source_processor.h"

TEST_CASE("Source Processor", "[SourceProcessor]") {
  Lexer lexer;

  // PKB dependencies:
  // Temp:
  class StorablePkbStub : public StorablePkb {
   public:
    void store(std::vector<AssignEntity> entities) override {}

    void store(std::vector<CallEntity> entities) override {}

    void store(std::vector<ConstantEntity> entities) override {}

    void store(std::vector<IfEntity> entities) override {}

    void store(std::vector<PrintEntity> entities) override {}

    void store(std::vector<ProcedureEntity> entities) override {}

    void store(std::vector<ReadEntity> entities) override {}

    void store(std::vector<VariableEntity> entities) override {}

    void store(std::vector<WhileEntity> entities) override {}

    void store(std::vector<FollowsAbstraction> abstractions) override {}

    void store(std::vector<FollowsTAbstraction> abstractions) override {}

    void store(std::vector<ModifiesSAbstraction> abstractions) override {}

    void store(std::vector<ParentTAbstraction> abstractions) override {}

    void store(std::vector<UsesSAbstraction> abstractions) override {}
  };

  StorablePkbStub storable_pkb_stub;

  // SP dependencies:
  SimpleParser simple_parser;

  AssignEntityNodeExtractor assign_entity_node_extractor;
  CallEntityNodeExtractor call_entity_node_extractor;
  ConstantEntityNodeExtractor constant_entity_node_extractor;
  IfEntityNodeExtractor if_entity_node_extractor;
  PrintEntityNodeExtractor print_entity_node_extractor;
  ProcedureEntityNodeExtractor procedure_entity_node_extractor;
  ReadEntityNodeExtractor read_entity_node_extractor;
  StatementEntityNodeExtractor statement_entity_node_extractor;
  VariableEntityNodeExtractor variable_entity_node_extractor;
  WhileEntityNodeExtractor while_entity_node_extractor;
  EntityExtractorImpl entity_extractor = EntityExtractorImpl(
      assign_entity_node_extractor, call_entity_node_extractor,
      constant_entity_node_extractor, if_entity_node_extractor,
      print_entity_node_extractor, procedure_entity_node_extractor,
      read_entity_node_extractor, statement_entity_node_extractor,
      variable_entity_node_extractor, while_entity_node_extractor);

  FollowsAbstractionExtractor follows_abstraction_extractor;
  FollowsTAbstractionExtractor follows_t_abstraction_extractor;
  AbstractionExtractorImpl abstraction_extractor = AbstractionExtractorImpl(
      follows_abstraction_extractor, follows_t_abstraction_extractor);

  DesignExtractorImpl design_extractor =
      DesignExtractorImpl(entity_extractor, abstraction_extractor);

  SourceProcessor source_processor_under_test = SourceProcessor(
      lexer, simple_parser, design_extractor, storable_pkb_stub);

  SECTION("Parse valid source file") {
    source_processor_under_test.Process(
        "../../../../Tests03/Sample_source.txt");
  }
}
