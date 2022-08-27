#include "catch.hpp"
#include "sp/extractor/entity/read_entity_node_extractor.h"

TEST_CASE("Read Entity Node Extractor", "[ReadEntityNodeExtractor]") {
  ReadEntityNodeExtractor extractor_under_test = ReadEntityNodeExtractor();

  SECTION("Extract Read Node") {
    TNode mock_read_node =
        TNode(TNode::Read, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<ReadEntity> maybe_read_entity =
        extractor_under_test.TryExtractFromNode(mock_read_node);
    ReadEntity read_entity = maybe_read_entity.value();
    REQUIRE(read_entity.GetLineNumber() == mock_read_node.GetLineNumber());
    REQUIRE(read_entity.GetNodePointer() == &mock_read_node);
  }

  SECTION("Extract empty from non-Read Node") {
    TNode mock_non_read_node =
        TNode(TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<ReadEntity> maybe_read_entity =
        extractor_under_test.TryExtractFromNode(mock_non_read_node);
    REQUIRE_FALSE(maybe_read_entity.has_value());
  }
}