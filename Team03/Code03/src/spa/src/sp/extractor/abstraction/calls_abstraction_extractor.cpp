#include "calls_abstraction_extractor.h"

std::vector<CallsAbstraction> CallsAbstractionExtractor::Extract(
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
  std::vector<CallsAbstraction> calls_abstractions = {};

  for (const auto &[parent, children] : proc_node_call_ent_umap) {
    auto lhs = t_node_proc_ent_umap.find(*parent)->second;
    for (const auto &child : children) {
      auto proc_node = proc_name_node_umap[child->GetStringValue()];
      auto rhs = t_node_proc_ent_umap.find(*proc_node)->second;
      calls_abstractions.emplace_back(lhs, rhs);
    }
  }
  return calls_abstractions;
}
