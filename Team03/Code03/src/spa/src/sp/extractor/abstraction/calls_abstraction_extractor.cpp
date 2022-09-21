#include "calls_abstraction_extractor.h"

#include <unordered_set>
#include <unordered_map>

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
    std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap) const {
  std::vector<CallsAbstraction> calls_abstractions = {};
  std::unordered_map<TNode*, std::unordered_set<TNode*>> procedure_mapping;

  for (const auto &call_entity : call_entities) {
    auto* curr_node_ptr = const_cast<TNode*>(call_entity.GetNodePointer());
    auto* parent_node_ptr = const_cast<TNode*> (curr_node_ptr->GetParent().get());

    if (procedure_mapping.find(parent_node_ptr) == procedure_mapping.end()) {
      std::unordered_set<TNode*> procedure_call_nodes = {curr_node_ptr};
      procedure_mapping[parent_node_ptr] = procedure_call_nodes;
    } else {
      procedure_mapping[parent_node_ptr].insert(curr_node_ptr);
    }
  }

  for (const auto& [parent, children] : procedure_mapping) {
    auto lhs = t_node_stmt_ent_umap.find(*parent)->second;
  }

  return calls_abstractions;
}
