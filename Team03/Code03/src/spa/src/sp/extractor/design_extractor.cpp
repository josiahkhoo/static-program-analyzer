#include "design_extractor.h"

DesignExtractor::DesignExtractor(
    const EntityExtractor& entity_extractor,
    const AbstractionExtractor& abstraction_extractor)
    : entity_extractor_(entity_extractor),
      abstraction_extractor_(abstraction_extractor) {}

DesignExtractorResult DesignExtractor::Extract(TNode ast) {
  EntityExtractorResult eer = entity_extractor_.Extract(ast);

  std::unordered_map<TNode, StatementEntity> t_node_stmt_ent_umap =
      GetTNodeStatementEntityMap(eer.GetStatementEntities());
  std::unordered_map<TNode, VariableEntity> t_node_var_ent_umap =
      GetTNodeVariableEntityMap(eer.GetVariableEntities());
  std::unordered_map<TNode, ConstantEntity> t_node_const_ent_umap =
      GetTNodeConstantEntityMap(eer.GetConstantEntities());

  AbstractionExtractorResult aer = abstraction_extractor_.Extract(
      eer, t_node_stmt_ent_umap, t_node_var_ent_umap, t_node_const_ent_umap);

  return {aer, eer};
}

std::unordered_map<TNode, StatementEntity>
DesignExtractor::GetTNodeStatementEntityMap(
    const std::vector<StatementEntity>& statement_entities) const {
  std::unordered_map<TNode, StatementEntity> umap;
  for (const auto& statement_entity : statement_entities)
    umap.insert({*statement_entity.GetNodePointer(), statement_entity});
  return umap;
}

std::unordered_map<TNode, VariableEntity>
DesignExtractor::GetTNodeVariableEntityMap(
    const std::vector<VariableEntity>& variable_entities) const {
  std::unordered_map<TNode, VariableEntity> umap;
  for (const auto& variable_entity : variable_entities)
    umap.insert({*variable_entity.GetNodePointer(), variable_entity});
  return umap;
}

std::unordered_map<TNode, ConstantEntity>
DesignExtractor::GetTNodeConstantEntityMap(
    const std::vector<ConstantEntity>& constant_entities) const {
  std::unordered_map<TNode, ConstantEntity> umap;
  for (const auto& constant_entity : constant_entities)
    umap.insert({*constant_entity.GetNodePointer(), constant_entity});
  return umap;
}
