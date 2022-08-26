//
// Created by Josiah Khoo on 27/8/22.
//

#include "variable_entity_node_extractor.h"

std::optional<VariableEntity> VariableEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::Variable)) {
    return {};
  }
  return std::make_optional<VariableEntity>(&ast, ast.GetStringValue().value());
}
