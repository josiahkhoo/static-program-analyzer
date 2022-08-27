#include "catch.hpp"
#include "sp/extractor/entity/variable_entity_node_extractor.h"

TEST_CASE("Variable Entity Node Extractor", "[VariableEntityNodeExtractor]") {
  VariableEntityNodeExtractor extractor_under_test =
      VariableEntityNodeExtractor();

  SECTION("Extract Variable Node") {
    TNode mock_variable_node = TNode(TNode::Variable, 1, "variable1");
    std::optional<VariableEntity> maybe_variable_entity =
        extractor_under_test.TryExtractFromNode(mock_variable_node);
    VariableEntity variable_entity = maybe_variable_entity.value();
    REQUIRE(variable_entity.GetName() == mock_variable_node.GetStringValue());
    REQUIRE(variable_entity.GetNodePointer() == &mock_variable_node);
  }

  SECTION("Extract empty from non-Variable Node") {
    TNode mock_non_variable_node =
        TNode(TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<VariableEntity> maybe_variable_entity =
        extractor_under_test.TryExtractFromNode(mock_non_variable_node);
    REQUIRE_FALSE(maybe_variable_entity.has_value());
  }
}