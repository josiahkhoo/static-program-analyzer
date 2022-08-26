//
// Created by Josiah Khoo on 27/8/22.
//

#include "print_entity_node_extractor.h"

std::optional<PrintEntity> PrintEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::Print)) {
    return {};
  }
  return std::make_optional<PrintEntity>(&ast, ast.GetLine());
}
