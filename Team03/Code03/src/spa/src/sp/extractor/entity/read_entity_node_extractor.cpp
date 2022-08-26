#include "read_entity_node_extractor.h"

std::optional<ReadEntity> ReadEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::Read)) {
    return {};
  }
  return std::make_optional<ReadEntity>(&ast, ast.GetLine());
}
