#include "uses_abstraction_extractor_impl.h"

std::pair<std::vector<UsesSAbstraction>, std::vector<UsesPAbstraction>>
UsesAbstractionExtractorImpl::Extract(
    const SubAbstractionExtractorContext& context) const {
  std::unordered_map<const TNode*, std::unordered_set<const TNode*>>
      proc_var_map;
  std::vector<UsesSAbstraction> uses_s_abstractions;
  std::vector<UsesPAbstraction> uses_p_abstractions;

  auto variable_entities = context.GetVariableEntities();
  auto call_entities = context.GetCallEntities();

  auto t_node_stmt_ent_umap = context.GetTNodeStmtEntUmap();
  auto proc_node_call_ent_umap = context.GetProcNodeCallEntUmap();
  auto t_node_proc_ent_umap = context.GetTNodeProcEntUmap();
  auto proc_name_node_umap = context.GetProcNameNodeUmap();
  auto t_node_var_ent_umap = context.GetTNodeVarEntUmap();

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
                 *curr_node_ptr->GetParent()->GetChildren()[1] ==
                     *curr_node_ptr) {
        // Do nothing here and continue
      } else if (curr_node_ptr->GetParent()->IsType(TNode::Assign) &&
                 *curr_node_ptr->GetParent()->GetChildren()[0] ==
                     *curr_node_ptr) {
        // Break if variable is on LHS of assign
        break;
      } else if (curr_node_ptr->IsType(TNode::Read)) {
        // Break if curr node is a read node
        break;
      }

      if (curr_node_ptr->IsStatement()) {
        // Look up for the statement entity form and use it in construction
        uses_s_abstractions.emplace_back(
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
      uses_p_abstractions.emplace_back(lhs, rhs);
    }
  }
  for (const auto& call_entity : call_entities) {
    auto call_node = call_entity.GetNodePointer();
    auto lhs = t_node_stmt_ent_umap.find(*call_node)->second;
    auto proc_node = proc_name_node_umap[call_node->GetStringValue()];
    for (const auto& var : proc_var_map[proc_node]) {
      auto rhs = t_node_var_ent_umap.find(*var)->second;
      uses_s_abstractions.emplace_back(lhs, rhs);
    }

    auto* curr_ptr = const_cast<TNode*>(call_node);
    while (curr_ptr != nullptr) {
      if (curr_ptr->IsType(TNode::Procedure)) {
        break;
      }
      if (curr_ptr->IsType(TNode::While) ||
          curr_ptr->IsType(TNode::IfElseThen)) {
        auto lhs2 = t_node_stmt_ent_umap.find(*curr_ptr)->second;
        for (const auto& var : proc_var_map[proc_node]) {
          auto rhs2 = t_node_var_ent_umap.find(*var)->second;
          uses_s_abstractions.emplace_back(lhs2, rhs2);
        }
      }
      curr_ptr = curr_ptr->GetParent().get();
    }
  }
  return {uses_s_abstractions, uses_p_abstractions};
}

void UsesAbstractionExtractorImpl::TraverseProcedureTree(
    std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap,
    std::unordered_map<std::string, const TNode*>& proc_name_node_umap,
    std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
        proc_node_call_ent_umap,
    std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
        proc_var_map,
    std::unordered_set<const TNode*>& children, const TNode* parent) const {
  std::unordered_set<const TNode*> visited;
  for (const auto& child : children) {
    auto proc_child_node = proc_name_node_umap[child->GetStringValue()];
    if (visited.find(proc_child_node) != visited.end()) {
      break;
    }
    visited.emplace(proc_child_node);
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