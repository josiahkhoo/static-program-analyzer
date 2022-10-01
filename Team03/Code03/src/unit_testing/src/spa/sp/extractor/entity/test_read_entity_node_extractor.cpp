#include "catch.hpp"
#include "sp/extractor/entity/read_entity_node_extractor.h"

TEST_CASE("Read Entity Node Extractor", "[ReadEntityNodeExtractor]") {
  ReadEntityNodeExtractor extractor_under_test = ReadEntityNodeExtractor();

  SECTION("Extract Read Node") {
    std::shared_ptr<TNode> mock_variable =
        std::make_shared<TNode>(2, TNode::Variable, 1, "x");
    TNode mock_read_node = TNode(
        1, TNode::Read, 1, std::vector<std::shared_ptr<TNode>>{mock_variable});
    std::optional<ReadEntity> maybe_read_entity =
        extractor_under_test.TryExtractFromNode(mock_read_node);
    ReadEntity read_entity = maybe_read_entity.value();
    REQUIRE(read_entity.GetStatementNumber() ==
            mock_read_node.GetStatementNumber());
    REQUIRE(read_entity.GetNodePointer() == &mock_read_node);
    REQUIRE(read_entity.GetVariableName() == "x");
  }

  SECTION("Extract empty from non-Read Node") {
    TNode mock_non_read_node =
        TNode(1, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<ReadEntity> maybe_read_entity =
        extractor_under_test.TryExtractFromNode(mock_non_read_node);
    REQUIRE_FALSE(maybe_read_entity.has_value());
  }
}