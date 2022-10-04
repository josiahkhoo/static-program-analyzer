#include <iostream>

#include "catch.hpp"
#include "common/lexer.h"
#include "cstdlib"
#include "pkb/pkb.h"
#include "qps/query_parser.h"
#include "qps/query_processing_subsystem.h"
#include "sp/extractor/abstraction/calls_abstraction_extractor.h"
#include "sp/extractor/abstraction/calls_t_abstraction_extractor.h"
#include "sp/extractor/abstraction/follows_abstraction_extractor.h"
#include "sp/extractor/abstraction/follows_t_abstraction_extractor.h"
#include "sp/extractor/abstraction/if_pattern_abstraction_extractor.h"
#include "sp/extractor/abstraction/modifies_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction/parent_abstraction_extractor.h"
#include "sp/extractor/abstraction/parent_t_abstraction_extractor.h"
#include "sp/extractor/abstraction/uses_abstraction_extractor_impl.h"
#include "sp/extractor/abstraction/while_pattern_abstraction_extractor.h"
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

  PKB pkb;

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
  ParentAbstractionExtractor parent_abstraction_extractor;
  ParentTAbstractionExtractor parent_t_abstraction_extractor;
  CallsAbstractionExtractor calls_abstraction_extractor;
  CallsTAbstractionExtractor calls_t_abstraction_extractor;
  UsesAbstractionExtractorImpl uses_abstraction_extractor;
  ModifiesAbstractionExtractorImpl modifies_abstraction_extractor;
  IfPatternAbstractionExtractor if_pattern_abstraction_extractor;
  WhilePatternAbstractionExtractor while_pattern_abstraction_extractor;
  AbstractionExtractorImpl abstraction_extractor = AbstractionExtractorImpl(
      follows_abstraction_extractor, follows_t_abstraction_extractor,
      parent_abstraction_extractor, parent_t_abstraction_extractor,
      calls_abstraction_extractor, calls_t_abstraction_extractor,
      if_pattern_abstraction_extractor, while_pattern_abstraction_extractor,
      uses_abstraction_extractor, modifies_abstraction_extractor);

  DesignExtractorImpl design_extractor =
      DesignExtractorImpl(entity_extractor, abstraction_extractor);

  SourceProcessor source_processor_under_test =
      SourceProcessor(lexer, simple_parser, design_extractor, pkb);

  SECTION("Parse valid source file") {
    std::string filepath = std::getenv("SAMPLE_SOURCE_PATH");
    source_processor_under_test.Process(filepath);
    Planner planner_;
    Evaluator evaluator_;

    QueryParser query_parser_;
    QueryProcessingSubsystem query_processing_subsystem_under_test =
        QueryProcessingSubsystem(lexer, query_parser_, planner_, evaluator_,
                                 pkb);

    std::string query = "assign a; Select a such that Follows(1, a)";
    std::list<std::string> res = {};
    query_processing_subsystem_under_test.Process(query, res);
  }
}
