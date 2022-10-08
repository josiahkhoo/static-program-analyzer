#include "sub_abstraction_extractor_context.h"

SubAbstractionExtractorContext::SubAbstractionExtractorContext(
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
    std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
    std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap,
    std::unordered_map<TNode, ConstantEntity> &t_node_const_ent_umap,
    std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap,
    std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
        &proc_node_call_ent_umap,
    std::unordered_map<std::string, const TNode *> &proc_name_node_umap)
    : assign_entities_(assign_entities),
      call_entities_(call_entities),
      constant_entities_(constant_entities),
      if_entities_(if_entities),
      print_entities_(print_entities),
      procedure_entities_(procedure_entities),
      read_entities_(read_entities),
      statement_entities_(statement_entities),
      variable_entities_(variable_entities),
      while_entities_(while_entities),
      t_node_stmt_ent_umap_(t_node_stmt_ent_umap),
      t_node_var_ent_umap_(t_node_var_ent_umap),
      t_node_const_ent_umap_(t_node_const_ent_umap),
      t_node_proc_ent_umap_(t_node_proc_ent_umap),
      proc_node_call_ent_umap_(proc_node_call_ent_umap),
      proc_name_node_umap_(proc_name_node_umap) {}

const std::vector<AssignEntity>
    &SubAbstractionExtractorContext::GetAssignEntities() const {
  return assign_entities_;
}

const std::vector<CallEntity> &SubAbstractionExtractorContext::GetCallEntities()
    const {
  return call_entities_;
}

const std::vector<ConstantEntity>
    &SubAbstractionExtractorContext::GetConstantEntities() const {
  return constant_entities_;
}

const std::vector<IfEntity> &SubAbstractionExtractorContext::GetIfEntities()
    const {
  return if_entities_;
}

const std::vector<PrintEntity>
    &SubAbstractionExtractorContext::GetPrintEntities() const {
  return print_entities_;
}

const std::vector<ProcedureEntity>
    &SubAbstractionExtractorContext::GetProcedureEntities() const {
  return procedure_entities_;
}

const std::vector<ReadEntity> &SubAbstractionExtractorContext::GetReadEntities()
    const {
  return read_entities_;
}

const std::vector<StatementEntity>
    &SubAbstractionExtractorContext::GetStatementEntities() const {
  return statement_entities_;
}

const std::vector<VariableEntity>
    &SubAbstractionExtractorContext::GetVariableEntities() const {
  return variable_entities_;
}

const std::vector<WhileEntity>
    &SubAbstractionExtractorContext::GetWhileEntities() const {
  return while_entities_;
}

std::unordered_map<TNode, StatementEntity>
    &SubAbstractionExtractorContext::GetTNodeStmtEntUmap() const {
  return t_node_stmt_ent_umap_;
}

std::unordered_map<TNode, VariableEntity>
    &SubAbstractionExtractorContext::GetTNodeVarEntUmap() const {
  return t_node_var_ent_umap_;
}

std::unordered_map<TNode, ConstantEntity>
    &SubAbstractionExtractorContext::GetTNodeConstEntUmap() const {
  return t_node_const_ent_umap_;
}

std::unordered_map<TNode, ProcedureEntity>
    &SubAbstractionExtractorContext::GetTNodeProcEntUmap() const {
  return t_node_proc_ent_umap_;
}

std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
    &SubAbstractionExtractorContext::GetProcNodeCallEntUmap() const {
  return proc_node_call_ent_umap_;
}

std::unordered_map<std::string, const TNode *>
    &SubAbstractionExtractorContext::GetProcNameNodeUmap() const {
  return proc_name_node_umap_;
}
