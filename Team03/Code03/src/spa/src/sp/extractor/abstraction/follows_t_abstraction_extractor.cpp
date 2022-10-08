#include "follows_t_abstraction_extractor.h"

std::vector<FollowsTAbstraction> FollowsTAbstractionExtractor::Extract(
    const SubAbstractionExtractorContext &context) const {
  std::vector<FollowsTAbstraction> follows_t_abstractions = {};
  auto procedure_entities = context.GetProcedureEntities();
  auto t_node_stmt_ent_umap = context.GetTNodeStmtEntUmap();
  auto while_entities = context.GetWhileEntities();
  auto if_entities = context.GetIfEntities();

  for (const auto &procedure_entity : procedure_entities) {
    RetrieveFromChildren(
        &follows_t_abstractions,
        procedure_entity.GetNodePointer()->GetChildren()[0]->GetChildren(),
        t_node_stmt_ent_umap);
  }
  for (const auto &while_entity : while_entities) {
    // Hacky way of retrieving while statements children, by assuming that it
    // has 2 children: {while_cond, stmt_list}
    RetrieveFromChildren(
        &follows_t_abstractions,
        while_entity.GetNodePointer()->GetChildren()[1]->GetChildren(),
        t_node_stmt_ent_umap);
  }
  for (const auto &if_entity : if_entities) {
    // Hacky way of retrieving the then and else statements,
    // Assumes that If Entity has 3 children, {if, then, else}
    std::vector<std::shared_ptr<TNode>> then_statements =
        if_entity.GetNodePointer()->GetChildren()[1]->GetChildren();
    RetrieveFromChildren(&follows_t_abstractions, then_statements,
                         t_node_stmt_ent_umap);
    std::vector<std::shared_ptr<TNode>> else_statements =
        if_entity.GetNodePointer()->GetChildren()[2]->GetChildren();
    RetrieveFromChildren(&follows_t_abstractions, else_statements,
                         t_node_stmt_ent_umap);
  }
  return follows_t_abstractions;
}

void FollowsTAbstractionExtractor::RetrieveFromChildren(
    std::vector<FollowsTAbstraction> *follows_t_abstractions,
    const std::vector<std::shared_ptr<TNode>> &children,
    std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap) const {
  for (int i = 0; i < (int)children.size() - 1; i++) {
    for (int j = i + 1; j < children.size(); j++) {
      auto lhs = t_node_stmt_ent_umap.find(*children[i])->second;
      auto rhs = t_node_stmt_ent_umap.find(*children[j])->second;
      follows_t_abstractions->emplace_back(lhs, rhs);
    }
  }
}
