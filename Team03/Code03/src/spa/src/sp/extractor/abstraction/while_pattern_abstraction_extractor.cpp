#include "while_pattern_abstraction_extractor.h"

std::vector<WhilePatternAbstraction> WhilePatternAbstractionExtractor::Extract(
    const std::vector<AssignEntity> &assign_entities,
    const std::vector<CallEntity> &call_entities,
    const std::vector<ConstantEntity> &constant_entities,
    const std::vector<IfEntity> &if_entities,
    const std::vector<PrintEntity> &print_entities,
    const std::vector<ProcedureEntity> &procedure_entities,
    const std::vector<ReadEntity> &read_entities,
    const std::vector<StatementEntity> &statement_entities,
    const std::vector<VariableEntity> &variable_entities,
    const std::vector<WhileEntity> &while_entities,
    std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
    std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap,
    std::unordered_map<TNode, ConstantEntity> &t_node_const_ent_umap,
    std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap,
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        &proc_node_call_ent_umap,
    std::unordered_map<std::string, const TNode *> &proc_name_node_umap) const {
  std::vector<WhilePatternAbstraction> while_pattern_abstractions;
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