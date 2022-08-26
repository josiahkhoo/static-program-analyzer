//
// Created by Josiah Khoo on 27/8/22.
//

#include "while_entity_node_extractor.h"

std::optional<WhileEntity> WhileEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::While)) {
    return {};
  }
  return std::make_optional<WhileEntity>(&ast, ast.GetLine());
}
