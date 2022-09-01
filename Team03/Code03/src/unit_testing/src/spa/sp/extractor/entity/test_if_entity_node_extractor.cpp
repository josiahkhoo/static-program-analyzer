#include "catch.hpp"
#include "sp/extractor/entity/if_entity_node_extractor.h"

TEST_CASE("If Entity Node Extractor", "[IfEntityNodeExtractor]") {
  IfEntityNodeExtractor extractor_under_test = IfEntityNodeExtractor();

  SECTION("Extract If Node") {
    TNode mock_if_node =
        TNode(0, TNode::IfElseThen, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<IfEntity> maybe_if_entity =
        extractor_under_test.TryExtractFromNode(mock_if_node);
    IfEntity if_entity = maybe_if_entity.value();
    REQUIRE(if_entity.GetLineNumber() == mock_if_node.GetStatementNumber());
    REQUIRE(if_entity.GetNodePointer() == &mock_if_node);
  }

  SECTION("Extract empty from non-If Node") {
    TNode mock_non_if_node =
        TNode(0, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<IfEntity> maybe_if_entity =
        extractor_under_test.TryExtractFromNode(mock_non_if_node);
    REQUIRE_FALSE(maybe_if_entity.has_value());
  }
}