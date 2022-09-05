#include "catch.hpp"
#include "sp/extractor/entity/constant_entity_node_extractor.h"

TEST_CASE("Constant Entity Node Extractor", "[ConstantEntityNodeExtractor]") {
    ConstantEntityNodeExtractor extractor_under_test =
            ConstantEntityNodeExtractor();

    SECTION("Extract Constant Node") {
        TNode mock_constant_node = TNode(1, TNode::Constant, 1, 2);
        std::optional<ConstantEntity> maybe_constant_entity =
                extractor_under_test.TryExtractFromNode(mock_constant_node);
        ConstantEntity constant_entity = maybe_constant_entity.value();
        REQUIRE(constant_entity.GetValue() == mock_constant_node.GetIntValue());
        REQUIRE(constant_entity.GetNodePointer() == &mock_constant_node);
    }

    SECTION("Extract empty from non-Constant Node") {
        TNode mock_non_constant_node =
                TNode(1, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
        std::optional<ConstantEntity> maybe_constant_entity =
                extractor_under_test.TryExtractFromNode(mock_non_constant_node);
        REQUIRE_FALSE(maybe_constant_entity.has_value());
    }
}