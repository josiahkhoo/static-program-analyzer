#include "parent_abstraction_extractor.h"

std::vector<ParentAbstraction> ParentAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<ParentAbstraction> parent_abstractions = {};

  auto while_entities = context.GetWhileEntities();
  auto if_entities = context.GetIfEntities();
  auto t_node_stmt_ent_umap = context.GetTNodeStmtEntUmap();

  for (const auto &while_entity : while_entities) {
    // Hacky way of retrieving while statements children, by assuming that it
    // has 2 children: {while_cond, stmt_list}
    auto lhs =
        t_node_stmt_ent_umap.find(*while_entity.GetNodePointer())->second;
    auto children =
        while_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    for (auto &i : children) {
      auto rhs = t_node_stmt_ent_umap.find(*i)->second;
      parent_abstractions.emplace_back(lhs, rhs);
    }
  }

  for (const auto &if_entity : if_entities) {
    // Hacky way of retrieving the then and else statements,
    // Assumes that If Entity has 3 children, {if, then, else}

    auto lhs = t_node_stmt_ent_umap.find(*if_entity.GetNodePointer())->second;
    std::vector<std::shared_ptr<TNode>> then_statements =
        if_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    for (auto &then_statement : then_statements) {
      auto rhs = t_node_stmt_ent_umap.find(*then_statement)->second;
      parent_abstractions.emplace_back(lhs, rhs);
    }
    std::vector<std::shared_ptr<TNode>> else_statements =
        if_entity.GetNodePointer()->GetChildren()[2]->GetChildren();
    for (auto &else_statement : else_statements) {
      auto rhs = t_node_stmt_ent_umap.find(*else_statement)->second;
      parent_abstractions.emplace_back(lhs, rhs);
    }
  }
  return parent_abstractions;
}
