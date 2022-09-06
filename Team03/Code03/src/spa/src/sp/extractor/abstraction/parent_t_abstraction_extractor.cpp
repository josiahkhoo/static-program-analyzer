#include "parent_t_abstraction_extractor.h"

std::vector<ParentTAbstraction> ParentTAbstractionExtractor::Extract(
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
    std::unordered_map<TNode, StatementEntity *> &t_node_stmt_ent_umap,
    std::unordered_map<TNode, VariableEntity *> &t_node_var_ent_umap,
    std::unordered_map<TNode, ConstantEntity *> &t_node_const_ent_umap) const {
  std::vector<ParentTAbstraction> parent_t_abstractions = {};

  for (const auto &while_entity : while_entities) {
    // Hacky way of retrieving while statements children, by assuming that it
    // has 2 children: {while_cond, stmt_list}
    auto lhs = t_node_stmt_ent_umap[*while_entity.GetNodePointer()];
    auto children = while_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    for (int i = 0; i < (int)children.size() - 1; i++) {
      auto rhs = t_node_stmt_ent_umap[*children[i]];
      parent_t_abstractions.emplace_back(lhs, rhs);
    }
  }
  for (const auto &if_entity : if_entities) {
    // Hacky way of retrieving the then and else statements,
    // Assumes that If Entity has 3 children, {if, then, else}
    auto lhs = t_node_stmt_ent_umap[*if_entity.GetNodePointer()];
    std::vector<std::shared_ptr<TNode>> then_statements =
        if_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    for (int i = 0; i < (int)then_statements.size() - 1; i++) {
      auto rhs = t_node_stmt_ent_umap[*then_statements[i]];
      parent_t_abstractions.emplace_back(lhs, rhs);
    }
    std::vector<std::shared_ptr<TNode>> else_statements =
        if_entity.GetNodePointer()->GetChildren()[2]->GetChildren();
    for (int i = 0; i < (int)else_statements.size() - 1; i++) {
      auto rhs = t_node_stmt_ent_umap[*else_statements[i]];
      parent_t_abstractions.emplace_back(lhs, rhs);
    }
  }
  return parent_t_abstractions;
}
