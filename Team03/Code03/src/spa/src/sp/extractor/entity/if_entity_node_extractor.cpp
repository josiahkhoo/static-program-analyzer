#include "if_entity_node_extractor.h"

std::optional<IfEntity> IfEntityNodeExtractor::TryExtractFromNode(
        const TNode &ast) const {
    if (ast.IsNotType(TNode::IfElseThen)) {
        return {};
    }
    return std::make_optional<IfEntity>(ast, ast.GetStatementNumber());
}
