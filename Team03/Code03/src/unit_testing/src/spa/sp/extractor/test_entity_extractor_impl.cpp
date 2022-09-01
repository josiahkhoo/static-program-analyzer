#include "catch.hpp"
#include "fakeit.hpp"
#include "sp/extractor/entity_extractor_impl.h"
using namespace fakeit;

TEST_CASE("Entity Extractor", "[EntityExtractor]") {
  Mock<AssignEntityNodeExtractor> mock_assign_extractor;
  When(Method(mock_assign_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<CallEntityNodeExtractor> mock_call_extractor;
  When(Method(mock_call_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<ConstantEntityNodeExtractor> mock_constant_extractor;
  When(Method(mock_constant_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<IfEntityNodeExtractor> mock_if_extractor;
  When(Method(mock_if_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<PrintEntityNodeExtractor> mock_print_extractor;
  When(Method(mock_print_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<ProcedureEntityNodeExtractor> mock_procedure_extractor;
  When(Method(mock_procedure_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<ReadEntityNodeExtractor> mock_read_extractor;
  When(Method(mock_read_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<StatementEntityNodeExtractor> mock_statement_extractor;
  When(Method(mock_statement_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<VariableEntityNodeExtractor> mock_variable_extractor;
  When(Method(mock_variable_extractor, TryExtractFromNode)).AlwaysReturn({});
  Mock<WhileEntityNodeExtractor> mock_while_extractor;
  When(Method(mock_while_extractor, TryExtractFromNode)).AlwaysReturn({});

  EntityExtractorImpl entity_extractor_under_test = EntityExtractorImpl(
      mock_assign_extractor.get(), mock_call_extractor.get(),
      mock_constant_extractor.get(), mock_if_extractor.get(),
      mock_print_extractor.get(), mock_procedure_extractor.get(),
      mock_read_extractor.get(), mock_statement_extractor.get(),
      mock_variable_extractor.get(), mock_while_extractor.get());

  SECTION("Extract single-depth node") {
    TNode single_depth_node = TNode(1, TNode::Constant, 1, 2);
    EntityExtractorResult res =
        entity_extractor_under_test.Extract(single_depth_node);
    Verify(Method(mock_assign_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_call_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_constant_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(
        Method(mock_if_extractor, TryExtractFromNode).Using(single_depth_node));
    Verify(Method(mock_while_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_variable_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_statement_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_read_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_procedure_extractor, TryExtractFromNode)
               .Using(single_depth_node));
    Verify(Method(mock_print_extractor, TryExtractFromNode)
               .Using(single_depth_node));

    VerifyNoOtherInvocations(Method(mock_assign_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_call_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_constant_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_if_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_while_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_variable_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_statement_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_read_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_procedure_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_print_extractor, TryExtractFromNode));

    mock_assign_extractor.ClearInvocationHistory();
    mock_call_extractor.ClearInvocationHistory();
    mock_constant_extractor.ClearInvocationHistory();
    mock_if_extractor.ClearInvocationHistory();
    mock_print_extractor.ClearInvocationHistory();
    mock_procedure_extractor.ClearInvocationHistory();
    mock_read_extractor.ClearInvocationHistory();
    mock_statement_extractor.ClearInvocationHistory();
    mock_variable_extractor.ClearInvocationHistory();
    mock_while_extractor.ClearInvocationHistory();
  }

  SECTION("Extract 2-depth node") {
    std::shared_ptr<TNode> shared_constant_node_ptr =
        std::make_shared<TNode>(1, TNode::Constant, 1, 2);
    std::shared_ptr<TNode> shared_variable_node_ptr =
        std::make_shared<TNode>(2, TNode::Variable, 1, "var");
    TNode assign_node =
        TNode(3, TNode::Assign, 1,
              {shared_variable_node_ptr, shared_constant_node_ptr});
    EntityExtractorResult res =
        entity_extractor_under_test.Extract(assign_node);

    Verify(
        Method(mock_assign_extractor, TryExtractFromNode).Using(assign_node));
    Verify(Method(mock_call_extractor, TryExtractFromNode).Using(assign_node));
    Verify(
        Method(mock_constant_extractor, TryExtractFromNode).Using(assign_node));
    Verify(Method(mock_if_extractor, TryExtractFromNode).Using(assign_node));
    Verify(Method(mock_while_extractor, TryExtractFromNode).Using(assign_node));
    Verify(
        Method(mock_variable_extractor, TryExtractFromNode).Using(assign_node));
    Verify(Method(mock_statement_extractor, TryExtractFromNode)
               .Using(assign_node));
    Verify(Method(mock_read_extractor, TryExtractFromNode).Using(assign_node));
    Verify(Method(mock_procedure_extractor, TryExtractFromNode)
               .Using(assign_node));
    Verify(Method(mock_print_extractor, TryExtractFromNode).Using(assign_node));

    Verify(Method(mock_assign_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_call_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_constant_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_if_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_while_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_variable_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_statement_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_read_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_procedure_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));
    Verify(Method(mock_print_extractor, TryExtractFromNode)
               .Using(*shared_variable_node_ptr));

    Verify(Method(mock_assign_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_call_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_constant_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_if_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_while_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_variable_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_statement_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_read_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_procedure_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));
    Verify(Method(mock_print_extractor, TryExtractFromNode)
               .Using(*shared_constant_node_ptr));

    VerifyNoOtherInvocations(Method(mock_assign_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_call_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_constant_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_if_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_while_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_variable_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_statement_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_read_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(
        Method(mock_procedure_extractor, TryExtractFromNode));
    VerifyNoOtherInvocations(Method(mock_print_extractor, TryExtractFromNode));

    mock_assign_extractor.ClearInvocationHistory();
    mock_call_extractor.ClearInvocationHistory();
    mock_constant_extractor.ClearInvocationHistory();
    mock_if_extractor.ClearInvocationHistory();
    mock_print_extractor.ClearInvocationHistory();
    mock_procedure_extractor.ClearInvocationHistory();
    mock_read_extractor.ClearInvocationHistory();
    mock_statement_extractor.ClearInvocationHistory();
    mock_variable_extractor.ClearInvocationHistory();
    mock_while_extractor.ClearInvocationHistory();
  }
}