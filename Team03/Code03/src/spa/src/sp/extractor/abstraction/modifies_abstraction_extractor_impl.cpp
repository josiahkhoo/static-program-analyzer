#include "modifies_abstraction_extractor_impl.h"

#include <iostream>

std::pair<std::vector<ModifiesSAbstraction>, std::vector<ModifiesPAbstraction>>
ModifiesAbstractionExtractorImpl::Extract(
    const std::vector<AssignEntity>& assign_entities,
    const std::vector<CallEntity>& call_entities,
    const std::vector<ConstantEntity>& constant_entities,
    const std::vector<IfEntity>& if_entities,
    const std::vector<PrintEntity>& print_entities,
    const std::vector<ProcedureEntity>& procedure_entities,
    const std::vector<ReadEntity>& read_entities,
    const std::vector<StatementEntity>& statement_entities,
    const std::vector<VariableEntity>& variable_entities,
    const std::vector<WhileEntity>& while_entities,
    std::unordered_map<TNode, StatementEntity>& t_node_stmt_ent_umap,
    std::unordered_map<TNode, VariableEntity>& t_node_var_ent_umap,
    std::unordered_map<TNode, ConstantEntity>& t_node_const_ent_umap,
    std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap,
    std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
        proc_node_call_ent_umap,
    std::unordered_map<std::string, const TNode*>& proc_name_node_umap) const {
  std::unordered_map<const TNode*, std::unordered_set<const TNode*>>
      proc_var_map;
  std::vector<ModifiesSAbstraction> modifies_s_abstractions;
  std::vector<ModifiesPAbstraction> modifies_p_abstractions;
  for (const auto& variable_entity : variable_entities) {
    auto* curr_node_ptr = const_cast<TNode*>(variable_entity.GetNodePointer());
    auto* var_node_ptr = const_cast<TNode*>(variable_entity.GetNodePointer());
    while (curr_node_ptr != nullptr) {
      if (curr_node_ptr->IsType(TNode::Procedure)) {
        if (proc_var_map.find(curr_node_ptr) != proc_var_map.end()) {
          proc_var_map[curr_node_ptr].emplace(var_node_ptr);
        } else {
          std::unordered_set<const TNode*> proc_var_nodes = {var_node_ptr};
          proc_var_map.emplace(curr_node_ptr, proc_var_nodes);
        }
        break;
      } else if (curr_node_ptr->GetParent()->IsType(TNode::Assign) &&
                 *curr_node_ptr->GetParent()->GetChildren()[0] !=
                     *curr_node_ptr) {
        // Break if variable is on RHS of assign
        break;
      } else if (curr_node_ptr->GetParent()->IsType(TNode::While) &&
                 *curr_node_ptr->GetParent()->GetChildren()[0] ==
                     *curr_node_ptr) {
        // Break if variable is on LHS of while
        break;
      } else if (curr_node_ptr->GetParent()->IsType(TNode::IfElseThen) &&
                 *curr_node_ptr->GetParent()->GetChildren()[0] ==
                     *curr_node_ptr) {
        // Break if variable is on LHS of if
        break;
      } else if (curr_node_ptr->IsType(TNode::Print)) {
        // Break if curr node is a print node
        break;
      }

      if (curr_node_ptr->IsStatement()) {
        // Look up for the statement entity form and use it in construction
        modifies_s_abstractions.emplace_back(
            t_node_stmt_ent_umap.find(*curr_node_ptr)->second, variable_entity);
      }
      curr_node_ptr = curr_node_ptr->GetParent().get();
    }
  }
  for (const auto& proc_pair : proc_node_call_ent_umap) {
    auto parent = proc_pair.first;
    auto children = proc_pair.second;
    TraverseProcedureTree(t_node_proc_ent_umap, proc_name_node_umap,
                          proc_node_call_ent_umap, proc_var_map, children,
                          parent);
  }
  for (const auto& proc_pair : proc_var_map) {
    auto proc_node_ptr = proc_pair.first;
    auto lhs = t_node_proc_ent_umap.find(*proc_node_ptr)->second;
    for (const auto& var : proc_var_map[proc_node_ptr]) {
      auto rhs = t_node_var_ent_umap.find(*var)->second;
      modifies_p_abstractions.emplace_back(lhs, rhs);
    }
  }
  for (const auto& call_entity : call_entities) {
    auto call_node = call_entity.GetNodePointer();
    auto lhs = t_node_stmt_ent_umap.find(*call_node)->second;
    auto proc_node = proc_name_node_umap[call_node->GetStringValue()];
    for (const auto& var : proc_var_map[proc_node]) {
      auto rhs = t_node_var_ent_umap.find(*var)->second;
      modifies_s_abstractions.emplace_back(lhs, rhs);
    }
  }

  return {modifies_s_abstractions, modifies_p_abstractions};
}

void ModifiesAbstractionExtractorImpl::TraverseProcedureTree(
    std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap,
    std::unordered_map<std::string, const TNode*>& proc_name_node_umap,
    std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
        proc_node_call_ent_umap,
    std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
        proc_var_map,
    std::unordered_set<const TNode*>& children, const TNode* parent) const {
  for (const auto& child : children) {
    auto proc_child_node = proc_name_node_umap[child->GetStringValue()];
    auto next_children = proc_node_call_ent_umap[proc_child_node];
    if (!next_children.empty()) {
      TraverseProcedureTree(t_node_proc_ent_umap, proc_name_node_umap,
                            proc_node_call_ent_umap, proc_var_map,
                            next_children, proc_child_node);
    }
    for (const auto& var : proc_var_map[proc_child_node]) {
      proc_var_map[parent].emplace(var);
    }
  }
}
