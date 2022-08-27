#include "catch.hpp"
#include "sp/extractor/entity/procedure_entity_node_extractor.h"

TEST_CASE("Procedure Entity Node Extractor", "[ProcedureEntityNodeExtractor]") {
  ProcedureEntityNodeExtractor extractor_under_test =
      ProcedureEntityNodeExtractor();

  SECTION("Extract Procedure Node") {
    TNode mock_procedure_node = TNode(TNode::Procedure, 1, "procedure");
    std::optional<ProcedureEntity> maybe_procedure_entity =
        extractor_under_test.TryExtractFromNode(mock_procedure_node);
    ProcedureEntity procedure_entity = maybe_procedure_entity.value();
    REQUIRE(procedure_entity.GetName() == mock_procedure_node.GetStringValue());
    REQUIRE(procedure_entity.GetNodePointer() == &mock_procedure_node);
  }

  SECTION("Extract empty from non-Procedure Node") {
    TNode mock_non_procedure_node =
        TNode(TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<ProcedureEntity> maybe_procedure_entity =
        extractor_under_test.TryExtractFromNode(mock_non_procedure_node);
    REQUIRE_FALSE(maybe_procedure_entity.has_value());
  }
}