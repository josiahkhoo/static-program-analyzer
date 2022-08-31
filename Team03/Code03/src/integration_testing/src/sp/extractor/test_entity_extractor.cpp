#include "catch.hpp"
#include "sp/extractor/entity_extractor_impl.h"

TEST_CASE("Entity Extractor", "[EntityExtractor]") {
  AssignEntityNodeExtractor assign_extractor = AssignEntityNodeExtractor();
  CallEntityNodeExtractor call_extractor = CallEntityNodeExtractor();
  ConstantEntityNodeExtractor constant_extractor =
      ConstantEntityNodeExtractor();
  IfEntityNodeExtractor if_extractor = IfEntityNodeExtractor();
  PrintEntityNodeExtractor print_extractor = PrintEntityNodeExtractor();
  ProcedureEntityNodeExtractor procedure_extractor =
      ProcedureEntityNodeExtractor();
  ReadEntityNodeExtractor read_extractor = ReadEntityNodeExtractor();
  StatementEntityNodeExtractor statement_extractor =
      StatementEntityNodeExtractor();
  VariableEntityNodeExtractor variable_extractor =
      VariableEntityNodeExtractor();
  WhileEntityNodeExtractor while_extractor = WhileEntityNodeExtractor();

  EntityExtractorImpl entity_extractor_under_test = EntityExtractorImpl(
      assign_extractor, call_extractor, constant_extractor, if_extractor,
      print_extractor, procedure_extractor, read_extractor, statement_extractor,
      variable_extractor, while_extractor);

  SECTION("Extract single-depth constant node") {
    TNode single_depth_node = TNode(TNode::Constant, 1, 2);
    EntityExtractorResult res =
        entity_extractor_under_test.Extract(single_depth_node);
    REQUIRE(res.GetAssignEntities().empty());
    REQUIRE(res.GetCallEntities().empty());
    REQUIRE(res.GetConstantEntities().size() == 1);
    REQUIRE(res.GetIfEntities().empty());
    REQUIRE(res.GetPrintEntities().empty());
    REQUIRE(res.GetProcedureEntities().empty());
    REQUIRE(res.GetReadEntities().empty());
    REQUIRE(res.GetStatementEntities().empty());
    REQUIRE(res.GetVariableEntities().empty());
    REQUIRE(res.GetWhileEntities().empty());
  }

  SECTION("Extract single-depth variable node") {
    TNode single_depth_node = TNode(TNode::Variable, 1, "var");
    EntityExtractorResult res =
        entity_extractor_under_test.Extract(single_depth_node);
    REQUIRE(res.GetAssignEntities().empty());
    REQUIRE(res.GetCallEntities().empty());
    REQUIRE(res.GetConstantEntities().empty());
    REQUIRE(res.GetIfEntities().empty());
    REQUIRE(res.GetPrintEntities().empty());
    REQUIRE(res.GetProcedureEntities().empty());
    REQUIRE(res.GetReadEntities().empty());
    REQUIRE(res.GetStatementEntities().empty());
    REQUIRE(res.GetVariableEntities().size() == 1);
    REQUIRE(res.GetWhileEntities().empty());
  }

  SECTION("Extract 2-depth assign constant variable node") {
    std::shared_ptr<TNode> shared_constant_node_ptr =
        std::make_shared<TNode>(TNode::Constant, 1, 2);
    std::shared_ptr<TNode> shared_variable_node_ptr =
        std::make_shared<TNode>(TNode::Variable, 1, "var");
    TNode assign_node = TNode(
        TNode::Assign, 1, {shared_variable_node_ptr, shared_constant_node_ptr});
    EntityExtractorResult res =
        entity_extractor_under_test.Extract(assign_node);
    REQUIRE(res.GetAssignEntities().size() == 1);
    REQUIRE(res.GetCallEntities().empty());
    REQUIRE(res.GetConstantEntities().size() == 1);
    REQUIRE(res.GetIfEntities().empty());
    REQUIRE(res.GetPrintEntities().empty());
    REQUIRE(res.GetProcedureEntities().empty());
    REQUIRE(res.GetReadEntities().empty());
    REQUIRE(res.GetStatementEntities().size() == 1);
    REQUIRE(res.GetVariableEntities().size() == 1);
    REQUIRE(res.GetWhileEntities().empty());

    REQUIRE(res.GetAssignEntities()[0].GetNodePointer() == &assign_node);
    REQUIRE(res.GetStatementEntities()[0].GetNodePointer() == &assign_node);

    REQUIRE(res.GetConstantEntities()[0].GetNodePointer() ==
            shared_constant_node_ptr.get());

    REQUIRE(res.GetVariableEntities()[0].GetNodePointer() ==
            shared_variable_node_ptr.get());
  }
}