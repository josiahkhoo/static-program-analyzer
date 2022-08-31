#include "catch.hpp"
#include "sp/extractor/entity/call_entity_node_extractor.h"

TEST_CASE("Call Entity Node Extractor", "[CallEntityNodeExtractor]") {
  CallEntityNodeExtractor extractor_under_test = CallEntityNodeExtractor();

  SECTION("Extract Call Node") {
    TNode mock_call_node =
        TNode(0, TNode::Call, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<CallEntity> maybe_call_entity =
        extractor_under_test.TryExtractFromNode(mock_call_node);
    CallEntity call_entity = maybe_call_entity.value();
    REQUIRE(call_entity.GetLineNumber() == mock_call_node.GetStatementNumber());
    REQUIRE(call_entity.GetNodePointer() == &mock_call_node);
  }

  SECTION("Extract empty from non-Call Node") {
    TNode mock_non_call_node =
        TNode(0, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<CallEntity> maybe_call_entity =
        extractor_under_test.TryExtractFromNode(mock_non_call_node);
    REQUIRE_FALSE(maybe_call_entity.has_value());
  }
}