#include "call_entity_node_extractor.h"

std::optional<CallEntity> CallEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::Call)) {
    return {};
  }
  return std::make_optional<CallEntity>(ast, ast.GetLineNumber());
}
