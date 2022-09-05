#include "statement_entity_node_extractor.h"

std::optional<StatementEntity> StatementEntityNodeExtractor::TryExtractFromNode(
    const TNode &ast) const {
  if (!ast.IsStatement()) {
    return {};
  }
  return std::make_optional<StatementEntity>(ast, ast.GetStatementNumber());
}
