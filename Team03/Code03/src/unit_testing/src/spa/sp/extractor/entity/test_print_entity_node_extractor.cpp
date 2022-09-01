#include "catch.hpp"
#include "sp/extractor/entity/print_entity_node_extractor.h"

TEST_CASE("Print Entity Node Extractor", "[PrintEntityNodeExtractor]") {
  PrintEntityNodeExtractor extractor_under_test = PrintEntityNodeExtractor();

  SECTION("Extract Print Node") {
    TNode mock_print_node =
        TNode(0, TNode::Print, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<PrintEntity> maybe_print_entity =
        extractor_under_test.TryExtractFromNode(mock_print_node);
    PrintEntity print_entity = maybe_print_entity.value();
    REQUIRE(print_entity.GetLineNumber() ==
            mock_print_node.GetStatementNumber());
    REQUIRE(print_entity.GetNodePointer() == &mock_print_node);
  }

  SECTION("Extract empty from non-Print Node") {
    TNode mock_non_print_node =
        TNode(0, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
    std::optional<PrintEntity> maybe_print_entity =
        extractor_under_test.TryExtractFromNode(mock_non_print_node);
    REQUIRE_FALSE(maybe_print_entity.has_value());
  }
}