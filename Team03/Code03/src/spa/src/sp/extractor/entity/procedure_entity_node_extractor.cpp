//
// Created by Josiah Khoo on 27/8/22.
//

#include "procedure_entity_node_extractor.h"

std::optional<ProcedureEntity> ProcedureEntityNodeExtractor::TryExtractFromNode(
    const TNode& ast) const {
  if (ast.IsNotType(TNode::IfElseThen)) {
    return {};
  }
  return std::make_optional<ProcedureEntity>(&ast, ast.GetStringValue().value());
}
