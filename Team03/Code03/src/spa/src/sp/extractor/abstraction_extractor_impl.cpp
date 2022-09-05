#include "abstraction_extractor_impl.h"

AbstractionExtractorImpl::AbstractionExtractorImpl(
    const SubAbstractionExtractor<FollowsAbstraction>
        &follows_abstraction_extractor,
    const SubAbstractionExtractor<FollowsTAbstraction>
        &follows_t_abstraction_extractor)
    : follows_abstraction_extractor_(follows_abstraction_extractor),
      follows_t_abstraction_extractor_(follows_t_abstraction_extractor) {}

AbstractionExtractorResult AbstractionExtractorImpl::Extract(
    const std::vector<AssignEntity> &assign_entities,
    const std::vector<CallEntity> &call_entities,
    const std::vector<ConstantEntity> &constant_entities,
    const std::vector<IfEntity> &if_entities,
    const std::vector<PrintEntity> &print_entities,
    const std::vector<ProcedureEntity> &procedure_entities,
    const std::vector<ReadEntity> &read_entities,
    const std::vector<StatementEntity> &statement_entities,
    const std::vector<VariableEntity> &variable_entities,
    const std::vector<WhileEntity> &while_entities) const {
  std::unordered_map<TNode, StatementEntity *> t_node_stmt_ent_umap =
      GetTNodeStatementEntityMap(statement_entities);
  std::unordered_map<TNode, VariableEntity *> t_node_var_ent_umap =
      GetTNodeVariableEntityMap(variable_entities);
  std::unordered_map<TNode, ConstantEntity *> t_node_const_ent_umap =
      GetTNodeConstantEntityMap(constant_entities);

  std::vector<FollowsAbstraction> follows_abstractions =
      follows_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap);

  std::vector<FollowsTAbstraction> follows_t_abstractions =
      follows_t_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap);

  return {follows_abstractions, follows_t_abstractions, {}, {}, {}, {}};
}

std::unordered_map<TNode, StatementEntity *>
AbstractionExtractorImpl::GetTNodeStatementEntityMap(
    const std::vector<StatementEntity> &statement_entities) const {
  std::unordered_map<TNode, StatementEntity *> umap;
  for (auto statement_entity : statement_entities)
    umap.insert_or_assign(*statement_entity.GetNodePointer(),
                          &statement_entity);
  return umap;
}

std::unordered_map<TNode, VariableEntity *>
AbstractionExtractorImpl::GetTNodeVariableEntityMap(
    const std::vector<VariableEntity> &variable_entities) const {
  std::unordered_map<TNode, VariableEntity *> umap;
  for (auto variable_entity : variable_entities)
    umap.insert_or_assign(*variable_entity.GetNodePointer(), &variable_entity);
  return umap;
}

std::unordered_map<TNode, ConstantEntity *>
AbstractionExtractorImpl::GetTNodeConstantEntityMap(
    const std::vector<ConstantEntity> &constant_entities) const {
  std::unordered_map<TNode, ConstantEntity *> umap;
  for (auto constant_entity : constant_entities)
    umap.insert_or_assign(*constant_entity.GetNodePointer(), &constant_entity);
  return umap;
}
