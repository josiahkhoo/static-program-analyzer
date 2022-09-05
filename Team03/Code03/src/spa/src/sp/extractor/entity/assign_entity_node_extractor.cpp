#include "assign_entity_node_extractor.h"

AssignEntityNodeExtractor::AssignEntityNodeExtractor() = default;

std::optional<AssignEntity> AssignEntityNodeExtractor::TryExtractFromNode(
    const TNode &ast) const {
  if (ast.IsNotType(TNode::Assign)) {
    return {};
  }
  return std::make_optional<AssignEntity>(ast, ast.GetStatementNumber());
}
