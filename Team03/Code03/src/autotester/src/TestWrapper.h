#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <iostream>
#include <list>
#include <string>

// include your other headers here
#include "AbstractWrapper.h"
#include "common/lexer.h"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/query_parser.h"
#include "qps/query_processing_subsystem.h"
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

class TestWrapper : public AbstractWrapper {
 public:
  // default constructor
  TestWrapper();

  // destructor
  ~TestWrapper();

  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);

  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);

 private:
  // Common dependencies:
  Lexer lexer_;

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

  StorablePkbStub storable_pkb_stub_;
  QueryablePkbStub queryable_pkb_stub_;

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

  FollowsAbstractionExtractor follows_abstraction_extractor_;
  FollowsTAbstractionExtractor follows_t_abstraction_extractor_;
  AbstractionExtractorImpl abstraction_extractor_ = AbstractionExtractorImpl(
      follows_abstraction_extractor_, follows_t_abstraction_extractor_);

  DesignExtractorImpl design_extractor_ =
      DesignExtractorImpl(entity_extractor_, abstraction_extractor_);

  SourceProcessor source_processor_ = SourceProcessor(
      lexer_, simple_parser_, design_extractor_, storable_pkb_stub_);

  // QPS dependencies:
  QueryParser query_parser_;
  Planner planner_;
  Evaluator evaluator_;

  QueryProcessingSubsystem query_processing_subsystem =
      QueryProcessingSubsystem(lexer_, query_parser_, planner_, evaluator_,
                               queryable_pkb_stub_);
};

#endif
