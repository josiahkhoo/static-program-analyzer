#include "abstraction_extractor_impl.h"

#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/uses_p_abstraction.h"

AbstractionExtractorImpl::AbstractionExtractorImpl(
    const SubAbstractionExtractor<FollowsAbstraction>
        &follows_abstraction_extractor,
    const SubAbstractionExtractor<FollowsTAbstraction>
        &follows_t_abstraction_extractor,
    const SubAbstractionExtractor<ParentAbstraction>
        &parent_abstraction_extractor,
    const SubAbstractionExtractor<ParentTAbstraction>
        &parent_t_abstraction_extractor,
    const UsesAbstractionExtractor &uses_abstraction_extractor,
    const ModifiesAbstractionExtractor &modifies_abstraction_extractor)
    : follows_abstraction_extractor_(follows_abstraction_extractor),
      follows_t_abstraction_extractor_(follows_t_abstraction_extractor),
      parent_abstraction_extractor_(parent_abstraction_extractor),
      parent_t_abstraction_extractor_(parent_t_abstraction_extractor),
      uses_abstraction_extractor_(uses_abstraction_extractor),
      modifies_abstraction_extractor_(modifies_abstraction_extractor) {}

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
  std::unordered_map<TNode, StatementEntity> t_node_stmt_ent_umap =
      GetTNodeStatementEntityMap(statement_entities);
  std::unordered_map<TNode, VariableEntity> t_node_var_ent_umap =
      GetTNodeVariableEntityMap(variable_entities);
  std::unordered_map<TNode, ConstantEntity> t_node_const_ent_umap =
      GetTNodeConstantEntityMap(constant_entities);
  std::unordered_map<TNode, ProcedureEntity> t_node_procedure_ent_umap =
      GetTNodeProcedureEntityMap(procedure_entities);

  std::vector<FollowsAbstraction> follows_abstractions =
      follows_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  std::vector<FollowsTAbstraction> follows_t_abstractions =
      follows_t_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  std::vector<ParentAbstraction> parent_abstractions =
      parent_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  std::vector<ParentTAbstraction> parent_t_abstractions =
      parent_t_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  auto [uses_s_abstractions, uses_p_abstractions] =
      uses_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  auto [modifies_s_abstractions, modifies_p_abstractions] =
      modifies_abstraction_extractor_.Extract(
          assign_entities, call_entities, constant_entities, if_entities,
          print_entities, procedure_entities, read_entities, statement_entities,
          variable_entities, while_entities, t_node_stmt_ent_umap,
          t_node_var_ent_umap, t_node_const_ent_umap,
          t_node_procedure_ent_umap);

  return {follows_abstractions,    follows_t_abstractions, parent_abstractions,
          parent_t_abstractions,   uses_s_abstractions,    uses_p_abstractions,
          modifies_s_abstractions, modifies_p_abstractions};
}

std::unordered_map<TNode, StatementEntity>
AbstractionExtractorImpl::GetTNodeStatementEntityMap(
    const std::vector<StatementEntity> &statement_entities) {
  std::unordered_map<TNode, StatementEntity> umap;
  for (const auto &statement_entity : statement_entities)
    umap.emplace(*statement_entity.GetNodePointer(), statement_entity);
  return umap;
}

std::unordered_map<TNode, VariableEntity>
AbstractionExtractorImpl::GetTNodeVariableEntityMap(
    const std::vector<VariableEntity> &variable_entities) {
  std::unordered_map<TNode, VariableEntity> umap;
  for (const auto &variable_entity : variable_entities)
    umap.emplace(*variable_entity.GetNodePointer(), variable_entity);
  return umap;
}

std::unordered_map<TNode, ConstantEntity>
AbstractionExtractorImpl::GetTNodeConstantEntityMap(
    const std::vector<ConstantEntity> &constant_entities) {
  std::unordered_map<TNode, ConstantEntity> umap;
  for (const auto &constant_entity : constant_entities)
    umap.emplace(*constant_entity.GetNodePointer(), constant_entity);
  return umap;
}

std::unordered_map<TNode, ProcedureEntity>
AbstractionExtractorImpl::GetTNodeProcedureEntityMap(
    const std::vector<ProcedureEntity> &procedure_entities) {
  std::unordered_map<TNode, ProcedureEntity> umap;
  for (const auto &procedure_entity : procedure_entities)
    umap.emplace(*procedure_entity.GetNodePointer(), procedure_entity);
  return umap;
}
