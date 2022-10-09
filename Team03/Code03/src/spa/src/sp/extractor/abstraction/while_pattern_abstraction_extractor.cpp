#include "while_pattern_abstraction_extractor.h"

std::vector<WhilePatternAbstraction> WhilePatternAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<WhilePatternAbstraction> while_pattern_abstractions;

  auto while_entities = context.GetWhileEntities();
  auto t_node_var_ent_umap = context.GetTNodeVarEntUmap();

  for (const auto &while_entity : while_entities) {
    auto condition = while_entity.GetNodePointer()->GetChildren()[0];
    RecursivelyExtractFromChildren(&while_pattern_abstractions, while_entity,
                                   condition->GetChildren(),
                                   t_node_var_ent_umap);
  }
  return while_pattern_abstractions;
}

void WhilePatternAbstractionExtractor::RecursivelyExtractFromChildren(
    std::vector<WhilePatternAbstraction> *while_pattern_abstractions,
    const WhileEntity &while_entity,
    const std::vector<std::shared_ptr<TNode>> &children,
    std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap) const {
  for (const auto &child : children) {
    if (child->IsType(TNode::Variable)) {
      while_pattern_abstractions->emplace_back(
          while_entity, t_node_var_ent_umap.find(*child)->second);
      continue;
    } else if (child->IsLeaf()) {
      continue;
    }
    RecursivelyExtractFromChildren(while_pattern_abstractions, while_entity,
                                   child->GetChildren(), t_node_var_ent_umap);
  }
}