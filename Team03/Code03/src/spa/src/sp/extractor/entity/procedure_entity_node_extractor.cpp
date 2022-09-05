#include "procedure_entity_node_extractor.h"

std::optional<ProcedureEntity> ProcedureEntityNodeExtractor::TryExtractFromNode(
        const TNode &ast) const {
    if (ast.IsNotType(TNode::Procedure)) {
        return {};
    }
    return std::make_optional<ProcedureEntity>(ast, ast.GetStringValue());
}
