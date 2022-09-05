#include "constant_entity_node_extractor.h"

std::optional<ConstantEntity> ConstantEntityNodeExtractor::TryExtractFromNode(
        const TNode &ast) const {
    if (ast.IsNotType(TNode::Constant)) {
        return {};
    }
    return std::make_optional<ConstantEntity>(ast, ast.GetIntValue());
}
