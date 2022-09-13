#include "uses_s_abstraction_extractor.h"

std::vector<UsesSAbstraction> UsesSAbstractionExtractor::Extract(
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
    std::unordered_map<TNode, ConstantEntity>& t_node_const_ent_umap) const {
  std::vector<UsesSAbstraction> uses_s_abstractions;
  for (const auto& variable_entity : variable_entities) {
    auto* curr_node_ptr = const_cast<TNode*>(variable_entity.GetNodePointer());
    while (curr_node_ptr != nullptr) {
      if (curr_node_ptr->IsType(TNode::Procedure)) {
        break;
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

  return uses_s_abstractions;
}
