#include "sp/extractor/entity_extractor.h"

#include "catch.hpp"

TEST_CASE("Entity Extractor", "[EntityExtractor]") {
  EntityExtractor entity_extractor_under_test = EntityExtractor(
      AssignEntityNodeExtractor(), CallEntityNodeExtractor(),
      ConstantEntityNodeExtractor(), IfEntityNodeExtractor(),
      PrintEntityNodeExtractor(), ProcedureEntityNodeExtractor(),
      ReadEntityNodeExtractor(), StatementEntityNodeExtractor(),
      VariableEntityNodeExtractor(), WhileEntityNodeExtractor());

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