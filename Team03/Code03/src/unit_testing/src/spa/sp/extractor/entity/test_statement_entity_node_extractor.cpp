#include "catch.hpp"
#include "sp/extractor/entity/statement_entity_node_extractor.h"

TEST_CASE("Statement Entity Node Extractor", "[StatementEntityNodeExtractor]") {
    StatementEntityNodeExtractor extractor_under_test =
            StatementEntityNodeExtractor();

    SECTION("Extract Statement Node") {
        TNode mock_statement_node =
                TNode(1, TNode::Assign, 1, std::vector<std::shared_ptr<TNode>>());
        std::optional<StatementEntity> maybe_statement_entity =
                extractor_under_test.TryExtractFromNode(mock_statement_node);
        StatementEntity statement_entity = maybe_statement_entity.value();
        REQUIRE(statement_entity.GetStatementNumber() ==
                mock_statement_node.GetStatementNumber());
        REQUIRE(statement_entity.GetNodePointer() == &mock_statement_node);
    }

    SECTION("Extract empty from non-Statement Node") {
        TNode mock_non_statement_node =
                TNode(1, TNode::And, 1, std::vector<std::shared_ptr<TNode>>());
        std::optional<StatementEntity> maybe_statement_entity =
                extractor_under_test.TryExtractFromNode(mock_non_statement_node);
        REQUIRE_FALSE(maybe_statement_entity.has_value());
    }
}