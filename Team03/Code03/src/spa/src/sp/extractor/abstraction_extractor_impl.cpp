#include "abstraction_extractor_impl.h"

#include <unordered_set>

AbstractionExtractorImpl::AbstractionExtractorImpl(
    const SubAbstractionExtractor<FollowsAbstraction>
        &follows_abstraction_extractor,
    const SubAbstractionExtractor<FollowsTAbstraction>
        &follows_t_abstraction_extractor,
    const SubAbstractionExtractor<ParentAbstraction>
        &parent_abstraction_extractor,
    const SubAbstractionExtractor<ParentTAbstraction>
        &parent_t_abstraction_extractor,
    const SubAbstractionExtractor<CallsAbstraction>
        &calls_abstraction_extractor,
    const SubAbstractionExtractor<CallsTAbstraction>
        &calls_t_abstraction_extractor,
    const SubAbstractionExtractor<IfPatternAbstraction>
        &if_pattern_abstraction_extractor,
    const SubAbstractionExtractor<WhilePatternAbstraction>
        &while_pattern_abstraction_extractor,
    const UsesAbstractionExtractor &uses_abstraction_extractor,
    const ModifiesAbstractionExtractor &modifies_abstraction_extractor)
    : follows_abstraction_extractor_(follows_abstraction_extractor),
      follows_t_abstraction_extractor_(follows_t_abstraction_extractor),
      parent_abstraction_extractor_(parent_abstraction_extractor),
      parent_t_abstraction_extractor_(parent_t_abstraction_extractor),
      calls_abstraction_extractor_(calls_abstraction_extractor),
      calls_t_abstraction_extractor_(calls_t_abstraction_extractor),
      if_pattern_abstraction_extractor_(if_pattern_abstraction_extractor),
      while_pattern_abstraction_extractor_(while_pattern_abstraction_extractor),
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
  std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
      proc_node_call_ent_umap = GetProcNodeCallEntityMap(call_entities);
  std::unordered_map<std::string, const TNode *> proc_name_node_umap =
      GetProcNameNodeMap(procedure_entities);

  SubAbstractionExtractorContext ctx =
      SubAbstractionExtractorContext::Builder()
          .AssignEntities(&assign_entities)
          .CallEntities(&call_entities)
          .ConstantEntities(&constant_entities)
          .IfEntities(&if_entities)
          .ProcedureEntities(&procedure_entities)
          .PrintEntities(&print_entities)
          .ReadEntities(&read_entities)
          .StatementEntities(&statement_entities)
          .VariableEntities(&variable_entities)
          .WhileEntities(&while_entities)
          .TNodeStmtEntUmap(&t_node_stmt_ent_umap)
          .TNodeVarEntUmap(&t_node_var_ent_umap)
          .TNodeConstEntUmap(&t_node_const_ent_umap)
          .TNodeProcEntUmap(&t_node_procedure_ent_umap)
          .ProcNodeCallEntUmap(&proc_node_call_ent_umap)
          .ProcNameNodeUmap(&proc_name_node_umap)
          .Build();

  std::vector<FollowsAbstraction> follows_abstractions =
      follows_abstraction_extractor_.Extract(ctx);

  std::vector<FollowsTAbstraction> follows_t_abstractions =
      follows_t_abstraction_extractor_.Extract(ctx);

  std::vector<ParentAbstraction> parent_abstractions =
      parent_abstraction_extractor_.Extract(ctx);

  std::vector<ParentTAbstraction> parent_t_abstractions =
      parent_t_abstraction_extractor_.Extract(ctx);

  std::vector<CallsAbstraction> calls_abstractions =
      calls_abstraction_extractor_.Extract(ctx);

  std::vector<CallsTAbstraction> calls_t_abstractions =
      calls_t_abstraction_extractor_.Extract(ctx);

  std::vector<IfPatternAbstraction> if_pattern_abstractions =
      if_pattern_abstraction_extractor_.Extract(ctx);

  std::vector<WhilePatternAbstraction> while_pattern_abstractions =
      while_pattern_abstraction_extractor_.Extract(ctx);

  auto [uses_s_abstractions, uses_p_abstractions] =
      uses_abstraction_extractor_.Extract(ctx);

  auto [modifies_s_abstractions, modifies_p_abstractions] =
      modifies_abstraction_extractor_.Extract(ctx);

  return AbstractionExtractorResult::Builder()
      .FollowsAbstractions(&follows_abstractions)
      .FollowsTAbstractions(&follows_t_abstractions)
      .ParentAbstractions(&parent_abstractions)
      .ParentTAbstractions(&parent_t_abstractions)
      .CallsAbstractions(&calls_abstractions)
      .CallsTAbstractions(&calls_t_abstractions)
      .UsesSAbstractions(&uses_s_abstractions)
      .UsesPAbstractions(&uses_p_abstractions)
      .ModifiesSAbstractions(&modifies_s_abstractions)
      .ModifiesPAbstractions(&modifies_p_abstractions)
      .IfPatternAbstractions(&if_pattern_abstractions)
      .WhilePatternAbstractions(&while_pattern_abstractions)
      .Build();
}

std::unordered_map<TNode, StatementEntity>
AbstractionExtractorImpl::GetTNodeStatementEntityMap(
    const std::vector<StatementEntity> &statement_entities) {
  std::unordered_map<TNode, StatementEntity> umap;
  umap.reserve(statement_entities.size());
  for (const auto &statement_entity : statement_entities)
    umap.emplace(*statement_entity.GetNodePointer(), statement_entity);
  return umap;
}

std::unordered_map<TNode, VariableEntity>
AbstractionExtractorImpl::GetTNodeVariableEntityMap(
    const std::vector<VariableEntity> &variable_entities) {
  std::unordered_map<TNode, VariableEntity> umap;
  umap.reserve(variable_entities.size());
  for (const auto &variable_entity : variable_entities)
    umap.emplace(*variable_entity.GetNodePointer(), variable_entity);
  return umap;
}

std::unordered_map<TNode, ConstantEntity>
AbstractionExtractorImpl::GetTNodeConstantEntityMap(
    const std::vector<ConstantEntity> &constant_entities) {
  std::unordered_map<TNode, ConstantEntity> umap;
  umap.reserve(constant_entities.size());
  for (const auto &constant_entity : constant_entities)
    umap.emplace(*constant_entity.GetNodePointer(), constant_entity);
  return umap;
}

std::unordered_map<TNode, ProcedureEntity>
AbstractionExtractorImpl::GetTNodeProcedureEntityMap(
    const std::vector<ProcedureEntity> &procedure_entities) {
  std::unordered_map<TNode, ProcedureEntity> umap;
  umap.reserve(procedure_entities.size());
  for (const auto &procedure_entity : procedure_entities)
    umap.emplace(*procedure_entity.GetNodePointer(), procedure_entity);
  return umap;
}

std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
AbstractionExtractorImpl::GetProcNodeCallEntityMap(
    const std::vector<CallEntity> &call_entities) {
  std::unordered_map<const TNode *, std::unordered_set<const TNode *>> umap;
  for (const auto &call_entity : call_entities) {
    auto *curr_node_ptr = const_cast<TNode *>(call_entity.GetNodePointer());
    auto *parent_node_ptr =
        const_cast<TNode *>(curr_node_ptr->GetParent().get());
    while (parent_node_ptr != nullptr) {
      if (parent_node_ptr->IsType(TNode::Procedure)) {
        break;
      }
      parent_node_ptr = parent_node_ptr->GetParent().get();
    }
    if (umap.find(parent_node_ptr) != umap.end()) {
      umap[parent_node_ptr].emplace(curr_node_ptr);
    } else {
      std::unordered_set<const TNode *> procedure_call_nodes = {curr_node_ptr};
      umap.emplace(parent_node_ptr, procedure_call_nodes);
    }
  }
  return umap;
}

std::unordered_map<std::string, const TNode *>
AbstractionExtractorImpl::GetProcNameNodeMap(
    const std::vector<ProcedureEntity> &procedure_entities) {
  std::unordered_map<std::string, const TNode *> umap;
  umap.reserve(procedure_entities.size());
  for (const auto &proc_entity : procedure_entities) {
    umap.emplace(proc_entity.GetName(), proc_entity.GetNodePointer());
  }
  return umap;
}
