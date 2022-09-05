#include "catch.hpp"
#include "sp/extractor/entity/assign_entity_node_extractor.h"

TEST_CASE("Assign Entity Node Extractor", "[AssignEntityNodeExtractor]") {
  AssignEntityNodeExtractor extractor_under_test = AssignEntityNodeExtractor();

  SECTION("Extract Assign Node") {
    TNode mock_assign_node =
        TNode(1, TNode::Assign, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<AssignEntity> maybe_assign_entity =
        extractor_under_test.TryExtractFromNode(mock_assign_node);
    AssignEntity assign_entity = maybe_assign_entity.value();
    REQUIRE(assign_entity.GetStatementNumber() ==
            mock_assign_node.GetStatementNumber());
    REQUIRE(assign_entity.GetNodePointer() == &mock_assign_node);
  }

  SECTION("Extract empty from non-Assign Node") {
    TNode mock_non_assign_node =
        TNode(1, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<AssignEntity> maybe_assign_entity =
        extractor_under_test.TryExtractFromNode(mock_non_assign_node);
    REQUIRE_FALSE(maybe_assign_entity.has_value());
  }
}