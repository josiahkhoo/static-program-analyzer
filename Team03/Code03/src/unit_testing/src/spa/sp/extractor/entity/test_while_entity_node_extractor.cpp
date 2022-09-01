#include "catch.hpp"
#include "sp/extractor/entity/while_entity_node_extractor.h"

TEST_CASE("While Entity Node Extractor", "[WhileEntityNodeExtractor]") {
  WhileEntityNodeExtractor extractor_under_test = WhileEntityNodeExtractor();

  SECTION("Extract While Node") {
    TNode mock_while_node =
        TNode(1, TNode::While, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<WhileEntity> maybe_while_entity =
        extractor_under_test.TryExtractFromNode(mock_while_node);
    WhileEntity while_entity = maybe_while_entity.value();
    REQUIRE(while_entity.GetLineNumber() ==
            mock_while_node.GetStatementNumber());
    REQUIRE(while_entity.GetNodePointer() == &mock_while_node);
  }

  SECTION("Extract empty from non-While Node") {
    TNode mock_non_while_node =
        TNode(1, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<WhileEntity> maybe_while_entity =
        extractor_under_test.TryExtractFromNode(mock_non_while_node);
    REQUIRE_FALSE(maybe_while_entity.has_value());
  }
}