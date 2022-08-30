//
// Created by Josiah Khoo on 30/8/22.
//

#include "follows_abstraction_extractor.h"

std::vector<FollowsAbstraction> FollowsAbstractionExtractor::Extract(
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
    std::unordered_map<TNode, StatementEntity*>& t_node_stmt_ent_umap,
    std::unordered_map<TNode, VariableEntity*>& t_node_var_ent_umap,
    std::unordered_map<TNode, ConstantEntity*>& t_node_const_ent_umap) const {
  std::vector<FollowsAbstraction> follows_abstractions = {};
  for (const auto& procedure_entity : procedure_entities) {
    RetrieveFromChildren(&follows_abstractions,
                         procedure_entity.GetNodePointer()->GetChildren(),
                         t_node_stmt_ent_umap);
  }
  for (const auto& while_entity : while_entities) {
    // Hacky way of retrieving while statements children, by assuming that it
    // has 2 children: {while_cond, stmt_list}
    RetrieveFromChildren(
        &follows_abstractions,
        while_entity.GetNodePointer()->GetChildren()[1]->GetChildren(),
        t_node_stmt_ent_umap);
  }
  for (const auto& if_entity : if_entities) {
    // Hacky way of retrieving the then and else statements,
    // Assumes that If Entity has 3 children, {if, then, else}
    std::vector<std::shared_ptr<TNode>> then_statements =
        if_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    RetrieveFromChildren(&follows_abstractions, then_statements,
                         t_node_stmt_ent_umap);
    std::vector<std::shared_ptr<TNode>> else_statements =
        if_entity.GetNodePointer()->GetChildren()[2]->GetChildren();
    RetrieveFromChildren(&follows_abstractions, else_statements,
                         t_node_stmt_ent_umap);
  }
  return follows_abstractions;
}

void FollowsAbstractionExtractor::RetrieveFromChildren(
    std::vector<FollowsAbstraction>* follows_abstractions,
    const std::vector<std::shared_ptr<TNode>>& children,
    std::unordered_map<TNode, StatementEntity*>& t_node_stmt_ent_umap) const {
  for (int i = 0; i < children.size() - 1; i++) {
    auto lhs = t_node_stmt_ent_umap[*children[i]];
    auto rhs = t_node_stmt_ent_umap[*children[i + 1]];
    follows_abstractions->emplace_back(*lhs, *rhs);
  }
}
