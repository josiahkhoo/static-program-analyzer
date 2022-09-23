#include "modifies_abstraction_extractor_impl.h"

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
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>&  proc_node_call_ent_umap,
    std::unordered_map<std::string, const TNode *>& proc_name_node_umap) const {
  std::vector<ModifiesSAbstraction> modifies_s_abstractions;
  std::vector<ModifiesPAbstraction> modifies_p_abstractions;
  for (const auto& variable_entity : variable_entities) {
    auto* curr_node_ptr = const_cast<TNode*>(variable_entity.GetNodePointer());
    while (curr_node_ptr != nullptr) {
      if (curr_node_ptr->IsType(TNode::Procedure)) {
        modifies_p_abstractions.emplace_back(
            t_node_proc_ent_umap.find(*curr_node_ptr)->second, variable_entity);
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
  return {modifies_s_abstractions, modifies_p_abstractions};
}
