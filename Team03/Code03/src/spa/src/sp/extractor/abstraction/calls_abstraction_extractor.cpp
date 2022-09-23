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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>&  proc_node_call_ent_umap,
    std::unordered_map<std::string, const TNode *>& proc_name_node_umap) const {
  std::vector<CallsAbstraction> calls_abstractions = {};
  std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
      procedure_mapping;
  std::unordered_map<std::string, const TNode *> proc_name_mapping;

  for (const auto &proc_entity : procedure_entities) {
    proc_name_mapping.insert(
        {proc_entity.GetName(), proc_entity.GetNodePointer()});
  }

  for (const auto &call_entity : call_entities) {
    auto *curr_node_ptr = const_cast<TNode *>(call_entity.GetNodePointer());
    auto *parent_node_ptr =
        const_cast<TNode *>(curr_node_ptr->GetParent().get());
    while (parent_node_ptr != nullptr) {
      if (parent_node_ptr->IsType(TNode::Procedure)) {
        break;
      }
      parent_node_ptr = parent_node_ptr->GetParent().get();
    }
    if (procedure_mapping.find(parent_node_ptr) != procedure_mapping.end()) {
      procedure_mapping[parent_node_ptr].insert(curr_node_ptr);
    } else {
      std::unordered_set<const TNode *> procedure_call_nodes = {curr_node_ptr};
      procedure_mapping.insert({parent_node_ptr, procedure_call_nodes});
    }
  }

  for (const auto &[parent, children] : procedure_mapping) {
    auto lhs = t_node_proc_ent_umap.find(*parent)->second;
    for (const auto &child : children) {
      auto proc_node = proc_name_mapping[child->GetStringValue()];
      auto rhs = t_node_proc_ent_umap.find(*proc_node)->second;
      calls_abstractions.emplace_back(lhs, rhs);
    }
  }
  return calls_abstractions;
}
