#ifndef SPA_SPA_H_
#define SPA_SPA_H_

#include "common/lexer.h"
#include "pkb/pkb.h"
#include "qps/evaluator.h"
#include "qps/planner.h"
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
#include "sp/extractor/cfg_extractor_impl.h"
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

class SPA {
 public:
  SPA();
  /// Parses the contents of the source into the SPA.
  /// \param filename Filename to Parse.
  void Parse(const std::string& filename);

  /// Evaluates a given string query and mutates the reference result passed in.
  /// \param query Query to execute.
  /// \param results Results to modify.
  void Evaluate(const std::string& query, std::list<std::string>& results);

 private:
  // Common dependencies:
  Lexer lexer_;

  // PKB dependencies:
  // Temp:
  PKB pkb_;
  StorablePkbImpl storable_pkb_;

  // SP dependencies:
  SimpleParser simple_parser_;

  AssignEntityNodeExtractor assign_entity_node_extractor_;
  CallEntityNodeExtractor call_entity_node_extractor_;
  ConstantEntityNodeExtractor constant_entity_node_extractor_;
  IfEntityNodeExtractor if_entity_node_extractor_;
  PrintEntityNodeExtractor print_entity_node_extractor_;
  ProcedureEntityNodeExtractor procedure_entity_node_extractor_;
  ReadEntityNodeExtractor read_entity_node_extractor_;
  StatementEntityNodeExtractor statement_entity_node_extractor_;
  VariableEntityNodeExtractor variable_entity_node_extractor_;
  WhileEntityNodeExtractor while_entity_node_extractor_;
  EntityExtractorImpl entity_extractor_ = EntityExtractorImpl(
      assign_entity_node_extractor_, call_entity_node_extractor_,
      constant_entity_node_extractor_, if_entity_node_extractor_,
      print_entity_node_extractor_, procedure_entity_node_extractor_,
      read_entity_node_extractor_, statement_entity_node_extractor_,
      variable_entity_node_extractor_, while_entity_node_extractor_);

  CFGExtractorImpl cfg_extractor_ = CFGExtractorImpl();

  FollowsAbstractionExtractor follows_abstraction_extractor_;
  FollowsTAbstractionExtractor follows_t_abstraction_extractor_;
  ParentAbstractionExtractor parent_abstraction_extractor_;
  ParentTAbstractionExtractor parent_t_abstraction_extractor_;
  CallsAbstractionExtractor calls_abstraction_extractor_;
  CallsTAbstractionExtractor calls_t_abstraction_extractor_;
  UsesAbstractionExtractorImpl uses_abstraction_extractor_;
  ModifiesAbstractionExtractorImpl modifies_abstraction_extractor_;
  IfPatternAbstractionExtractor if_pattern_abstraction_extractor_;
  WhilePatternAbstractionExtractor while_pattern_abstraction_extractor_;
  AbstractionExtractorImpl abstraction_extractor_ = AbstractionExtractorImpl(
      follows_abstraction_extractor_, follows_t_abstraction_extractor_,
      parent_abstraction_extractor_, parent_t_abstraction_extractor_,
      calls_abstraction_extractor_, calls_t_abstraction_extractor_,
      if_pattern_abstraction_extractor_, while_pattern_abstraction_extractor_,
      uses_abstraction_extractor_, modifies_abstraction_extractor_);

  DesignExtractorImpl design_extractor_ = DesignExtractorImpl(
      entity_extractor_, cfg_extractor_, abstraction_extractor_);

  SourceProcessor source_processor_ =
      SourceProcessor(lexer_, simple_parser_, design_extractor_, storable_pkb_);

  // QPS dependencies:
  QueryParser query_parser_;
  Planner planner_;
  Evaluator evaluator_;

  QueryProcessingSubsystem query_processing_subsystem =
      QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                               pkb_);
};

#endif  // SPA_SPA_H_
