#include "if_pattern_abstraction_extractor.h"

std::vector<IfPatternAbstraction> IfPatternAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<IfPatternAbstraction> if_pattern_abstractions;
  auto if_entities = context.GetIfEntities();
  auto t_node_var_ent_umap = context.GetTNodeVarEntUmap();

  for (const auto &if_entity : if_entities) {
    auto condition = if_entity.GetNodePointer()->GetChildren()[0];
    RecursivelyExtractFromChildren(&if_pattern_abstractions, if_entity,
                                   condition->GetChildren(),
                                   t_node_var_ent_umap);
  }
  return if_pattern_abstractions;
}

void IfPatternAbstractionExtractor::RecursivelyExtractFromChildren(
    std::vector<IfPatternAbstraction> *if_pattern_abstractions,
    const IfEntity &if_entity,
    const std::vector<std::shared_ptr<TNode>> &children,
    std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap) const {
  for (const auto &child : children) {
    if (child->IsType(TNode::Variable)) {
      if_pattern_abstractions->emplace_back(
          if_entity, t_node_var_ent_umap.find(*child)->second);
      continue;
    } else if (child->IsLeaf()) {
      continue;
    }
    RecursivelyExtractFromChildren(if_pattern_abstractions, if_entity,
                                   child->GetChildren(), t_node_var_ent_umap);
  }
}
